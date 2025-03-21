#include "pelengbase.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <QDebug>

namespace qmapcontrol
{
    int sign(qreal val)
    {
        return signbit(val) ? -1 : 1;
    }

    void PelengBase::calculate(QPointF position, qreal azimuth, qreal length, QPolygonF &peleng)
    {
        peleng.clear();

        qreal delta = 1.0 / PELENG_DELTA_MULT;

        Quaternion q(0, 0, 0, 0);

        qreal a = azimuth;
        while (a > 180) a -= 360.0;
        while (a < -180) a += 360.0;

        // преобразование азимута из x0 в y0
        a = 90.0 - a;


        // опредляем смещение начальной точки за 90 градусов
        // для того, чтобы отсчет начинался всегда из промежутка -90*90
        qreal xoffset = 0;
        while ((position.x() - xoffset) > 90.0) xoffset += 90.0;
        while ((position.x() - xoffset) < -90.0) xoffset -= 90.0;

        _getBaseQuats(position.x() - xoffset, position.y(), a, q);


        a = qAbs(a); // необходимо ниже для корректной отрисовки вертикального пеленга
        qreal prevX = -M_PI;
        qreal prevY = -M_PI;
        int dirX = 1;
        int dirY = 0;

        qreal pStart, pEnd;
        pStart = 0;
        pEnd = 360. * length / EARTH_EQUATOR_LENGTH;
        pEnd = pStart + pEnd;

        // необходимо заранее определить направление движения
        Quaternion p(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        //Quaternion pi = Quaternion(0, 1, 0, 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);

        qreal prevPi = p.i;
        qreal prevPj = p.j;

        qreal v = asin(p.k);
        qreal u = asin(p.j / cos(v));
        prevX = u;
        prevY = v;

        //delta = qMin(delta, qMax(pEnd - pStart, delta));
        if (pEnd - pStart < delta && pEnd != pStart)
        {
            delta = pEnd - pStart;
            if (delta < 0.000001)
                delta = 0.001;
        }
        pStart += delta;

        p = Quaternion(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);
        v = asin(p.k);
        u = asin(p.j / cos(asin(p.k)));
        //v = M_PI / 2 - v;
        if (qAbs(u - prevX) > 0.00001)
        {
            if (u > prevX) dirX = 1;
            else dirX = -1;
        }

        prevX = rad_deg(prevX);
        prevY = rad_deg(prevY);
        peleng.append(QPointF(prevX + xoffset, prevY));

        qreal sdir = dirX;
        dirX = 0;

        while (pStart <= pEnd)
        {
            p = Quaternion(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
            p = q.mul(p.mul(q.inverse()));

            p.k = qBound(-1.0, p.k, 1.0);
            qreal v, u;

            v = asin(p.k);
            if (qAbs(cos(v)) < 0.000001)
            {
                u = deg_rad(position.x() + xoffset); // 0;
            }
            else
            {
                u = p.j / cos(v);
                u = qBound(-1.0, u, 1.0);
                u = asin(u);
            }

            u = rad_deg(u);
            v = rad_deg(v);

            // проверяем, что расчет перешагнул через полюс
            if (sign(prevPi) * sign(p.i) < 0 && sign(prevPj) * sign(p.j) < 0)
            {
                dirY += 1;
            }
            else if (v == -90) // затычка, т.к. результат u получается противоположный -89 градусам, а должен сохраняться
            {
                p.i *= -1;
                p.j *= -1;
                dirY += 1;
            }
            // данной строчкой убираем "дребезг" вокруг одной и той же координаты X 
            else if(qAbs(u - prevX) > 0.00001)// && a != 90.0)
            {
                // проверяем, что расчет перешагнул через одну из границ 90/-90
                if (prevPi * p.i < 0)
                {
                    dirX++;
                }
            }

            prevPi = p.i;
            prevPj = p.j;

            // для вертикального пеленга корректируем координату x при прохождении через полюса
            if (dirY % 2 != 0) u = 180 - u;

            u = u * ((dirX % 2) == 0 ? 1 : -1)
                + sdir * 180 * dirX + xoffset;

            prevX = u;

            peleng.append(QPointF(u, v));

            //delta = qMin(delta, qMax(pEnd - pStart, delta));
            if (pEnd - pStart < delta && pEnd != pStart)
            {
                delta = pEnd - pStart;
            }
            pStart += delta;
        }

        optimizePolygon(peleng);
    }

    void PelengBase::calculate(QPointF position, qreal azimuth, qreal length, qreal deltaMultiplier, QPolygonF &peleng)
    {
        peleng.clear();

        qreal delta = 1.0 / PELENG_DELTA_MULT * deltaMultiplier;

        Quaternion q(0, 0, 0, 0);

        qreal a = azimuth;
        while (a > 180) a -= 360.0;
        while (a < -180) a += 360.0;

        // преобразование азимута из x0 в y0
        a = 90.0 - a;

        // опредляем смещение начальной точки за 90 градусов
        // для того, чтобы отсчет начинался всегда из промежутка -90*90
        qreal xoffset = 0;
        while ((position.x() - xoffset) > 90.0) xoffset += 90.0;
        while ((position.x() - xoffset) < -90.0) xoffset -= 90.0;

        _getBaseQuats(position.x() - xoffset, position.y(), a, q);


        a = qAbs(a); // необходимо ниже для корректной отрисовки вертикального пеленга
        qreal prevX = -M_PI;
        qreal prevY = -M_PI;
        int dirX = 1;
        int dirY = 0;

        qreal pStart, pEnd;
        pStart = 0;
        pEnd = 360. * length / EARTH_EQUATOR_LENGTH;
        pEnd = pStart + pEnd;

        // необходимо заранее определить направление движения
        Quaternion p(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        //Quaternion pi = Quaternion(0, 1, 0, 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);

        qreal prevPi = p.i;
        qreal prevPj = p.j;

        qreal v = asin(p.k);
        qreal u = asin(p.j / cos(v));
        prevX = u;
        prevY = v;

        if (pEnd - pStart < delta && pEnd != pStart)
        {
            delta = pEnd - pStart;
            if (delta < 0.000001)
                delta = 0.001;
        }
        pStart += delta;

        p = Quaternion(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);
        v = asin(p.k);
        u = asin(p.j / cos(asin(p.k)));
        //v = M_PI / 2 - v;
        if (qAbs(u - prevX) > 0.00001)
        {
            if (u > prevX) dirX = 1;
            else dirX = -1;
        }

        prevX = rad_deg(prevX);
        prevY = rad_deg(prevY);
        peleng.append(QPointF(prevX + xoffset, prevY));

        qreal sdir = dirX;
        dirX = 0;

        while (pStart <= pEnd)
        {
            p = Quaternion(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
            p = q.mul(p.mul(q.inverse()));

            p.k = qBound(-1.0, p.k, 1.0);
            qreal v, u;

            v = asin(p.k);
            if (qAbs(cos(v)) < 0.000001)
            {
                u = deg_rad(position.x() + xoffset); // 0;
            }
            else
            {
                u = p.j / cos(v);
                u = qBound(-1.0, u, 1.0);
                u = asin(u);
            }

            u = rad_deg(u);
            v = rad_deg(v);

            // проверяем, что расчет перешагнул через полюс
            if (sign(prevPi) * sign(p.i) < 0 && sign(prevPj) * sign(p.j) < 0)
            {
                dirY += 1;
            }
            else if (v == -90) // затычка, т.к. результат u получается противоположный -89 градусам, а должен сохраняться
            {
                p.i *= -1;
                p.j *= -1;
                dirY += 1;
            }
            // данной строчкой убираем "дребезг" вокруг одной и той же координаты X 
            else if (qAbs(u - prevX) > 0.00001)// && a != 90.0)
            {
                // проверяем, что расчет перешагнул через одну из границ 90/-90
                if (prevPi * p.i < 0)
                {
                    dirX++;
                }
            }

            prevPi = p.i;
            prevPj = p.j;

            // для вертикального пеленга корректируем координату x при прохождении через полюса
            if (dirY % 2 != 0) u = 180 - u;

            u = u * ((dirX % 2) == 0 ? 1 : -1)
                + sdir * 180 * dirX + xoffset;

            prevX = u;

            peleng.append(QPointF(u, v));

            //delta = qMin(delta, qMax(pEnd - pStart, delta));
            if (pEnd - pStart < delta && pEnd != pStart)
            {
                delta = pEnd - pStart;
            }
            pStart += delta;
        }

        optimizePolygon(peleng);
    }

    void PelengBase::calculateEndPoint(QPointF position, qreal azimuth, qreal length, QPointF &end)
    {
        Quaternion q(0, 0, 0, 0);

        qreal a = azimuth;
        while (a > 180) a -= 360.0;
        while (a < -180) a += 360.0;

        // преобразование азимута из x0 в y0
        a = 90.0 - a;

        // опредляем смещение начальной точки за 90 градусов
        // для того, чтобы отсчет начинался всегда из промежутка -90*90
        qreal xoffset = 0;
        while ((position.x() - xoffset) > 90.0) xoffset += 90.0;
        while ((position.x() - xoffset) < -90.0) xoffset -= 90.0;

        _getBaseQuats(position.x() - xoffset, position.y(), a, q);


        a = qAbs(a); // необходимо ниже для корректной отрисовки вертикального пеленга
        qreal prevX = -M_PI;
        qreal prevY = -M_PI;
        int dirX = 1;
        int dirY = 0;

        qreal pStart, pEnd;
        pStart = 0;
        pEnd = 360. * length / EARTH_EQUATOR_LENGTH;
        qreal delta = pEnd;
        pEnd = pStart + pEnd;


        // необходимо заранее определить направление движения
        Quaternion p(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        //Quaternion pi = Quaternion(0, 1, 0, 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);

        qreal prevPi = p.i;
        qreal prevPj = p.j;

        qreal v = asin(p.k);
        qreal u = asin(p.j / cos(v));
        prevX = u;
        prevY = v;

        if (pEnd - pStart < delta && pEnd != pStart)
        {
            delta = pEnd - pStart;
        }

        pStart += 0.01;//delta;
        p = Quaternion(0, cos(deg_rad(pStart)), sin(deg_rad(pStart)), 0);
        p = q.mul(p.mul(q.inverse()));
        p.k = qBound(-1.0, p.k, 1.0);
        v = asin(p.k);
        u = asin(p.j / cos(v));
        if (qAbs(u - prevX) > 0.00001)
        {
            if (u > prevX) dirX = 1;
            else dirX = -1;
        }

        prevX = rad_deg(prevX);
        prevY = rad_deg(prevY);

        qreal sdir = dirX;
        dirX = 0;


        // -------------------
        p = Quaternion(0, cos(deg_rad(pEnd)), sin(deg_rad(pEnd)), 0);
        p = q.mul(p.mul(q.inverse()));

        p.k = qBound(-1.0, p.k, 1.0);

        v = asin(p.k);
        if (qAbs(cos(v)) < 0.000001)
        {
            u = deg_rad(position.x() + xoffset); // 0;
        }
        else
        {
            u = p.j / cos(v);
            u = qBound(-1.0, u, 1.0);
            u = asin(u);
        }

        u = rad_deg(u);
        v = rad_deg(v);

        // проверяем, что расчет перешагнул через полюс
        if (sign(prevPi) * sign(p.i) < 0 && sign(prevPj) * sign(p.j) < 0)
        {
            dirY += 1;
        }
        else if (v == -90) // затычка, т.к. результат u получается противоположный -89 градусам, а должен сохраняться
        {
            p.i *= -1;
            p.j *= -1;
            dirY += 1;
        }
        // данной строчкой убираем "дребезг" вокруг одной и той же координаты X 
        else if (qAbs(u - prevX) > 0.00001)// && a != 90.0)
        {
            // проверяем, что расчет перешагнул через одну из границ 90/-90
            if (prevPi * p.i < 0)
            {
                dirX++;
            }
        }

        // для вертикального пеленга корректируем координату x при прохождении через полюса
        if (dirY % 2 != 0) u = 180 - u;

        u = u * ((dirX % 2) == 0 ? 1 : -1)
            + sdir * 180 * dirX + xoffset;

        // -------------------

        end = QPointF(u + xoffset, v);
    }

    void PelengBase::_getBaseQuats(qreal angX, qreal angY, qreal angK, Quaternion &q)
    {
        Quaternion qx = Quaternion(
            cos(deg_rad(angX / 2)),
            0 * sin(deg_rad(angX / 2)),
            0 * sin(deg_rad(angX / 2)),
            1 * sin(deg_rad(angX / 2))
            );

        Quaternion p = Quaternion(0, 1, 0, 0);

        p = qx.mul(p.mul(qx.inverse()));

        Quaternion q90 = Quaternion(
            cos(deg_rad(angY / 2)),
            p.j * sin(deg_rad(angY / 2)),
            -p.i * sin(deg_rad(angY / 2)),
            0 * sin(deg_rad(angY / 2))
            );

        p = q90.mul(p.mul(q90.inverse()));

        Quaternion t = p;
        t.r = 0;
        t = t.unit();
        Quaternion qK = Quaternion(
            cos(deg_rad(angK / 2)),
            t.i * sin(deg_rad(angK / 2)),
            t.j * sin(deg_rad(angK / 2)),
            t.k * sin(deg_rad(angK / 2))
            );

        q = qK.mul(q90.mul(qx));
    }

    void PelengBase::splitByMapBorders(QPolygonF &peleng, QList<QPolygonF*> &splittedPeleng)
    {
        _splitVerticiesByBorders(&peleng, &splittedPeleng);
    }

    QPointF PelengBase::borderedPoint(QPointF p)
    {
        while (p.x() > 180) p.rx() -= 360;
        while (p.x() < -180) p.rx() += 360;

        return p;
    }

    void PelengBase::_splitVerticiesByBorders(QPolygonF *vert, QList<QPolygonF*> *polygons)
    {
        if (vert->count() < 2) return;

        QPolygonF *curPoly = new QPolygonF();
        polygons->append(curPoly);

        QPointF delta = QPointF(0, 0);
        QPointF ps, p;
        for (int i = 0; i < vert->count(); i++)
        {
            p = vert->at(i);
            // проверяем на выход за пределы области карты
            while (p.x() > 180) p.rx() -= 360.0;
            while (p.x() < -180) p.rx() += 360.0;
            if (ps.isNull()) ps = p;

            if (sign(p.x()) != sign(ps.x()))
            {
                // определяем границу
                qreal x = ps.x() - p.x();
                qreal bx = qBound(-180.0, x, 180.0);
                if (bx != x) // это исключает дробление при переходе через 0
                {
                    // дробим по границе
                    QPointF pp = QPointF(bx, f(ps, p + QPointF(bx * 2, 0), bx));

                    curPoly->append(pp);

                    curPoly = new QPolygonF();
                    polygons->append(curPoly);
                    pp.rx() = -pp.x();
                    curPoly->append(pp);
                }
            }

            curPoly->append(p);

            ps = p;
        }
    }

    qreal PelengBase::f(QPointF pb, QPointF pe, qreal x)
    {
        return (x - pb.x()) * (pe.y() - pb.y()) / (pe.x() - pb.x()) + pb.y();
    }

    qreal PelengBase::x(QPointF pb, QPointF pe, qreal y)
    {
        return (y - pb.y()) * (pe.x() - pb.x()) / (pe.y() - pb.y()) + pb.x();
    }

    qreal PelengBase::deg_rad(qreal x)
    {
        return x * (M_PI / 180.0);
    }

    qreal PelengBase::rad_deg(qreal x)
    {
        return x * (180 / M_PI);
    }

    void PelengBase::optimizePolygon(QPolygonF &polygon)
    {
        if (polygon.count() < 3) return;

        int i = 1, is = 0;
        QPointF ps = polygon.at(is);
        while (polygon.count() > i)
        {
            QPointF p = polygon.at(i);
            while (ps.x() == p.x())
            {
                if (i - is > 1)
                {
                    polygon.remove(i - 1);
                    i--;
                }
                i++;
                if (!(polygon.count() > i)) break;
                p = polygon.at(i);
            }

            while (ps.y() == p.y())
            {
                if (i - is > 1)
                {
                    polygon.remove(i - 1);
                    i--;
                }
                i++;
                if (!(polygon.count() > i)) break;
                p = polygon.at(i);
            }

            if (!(polygon.count() > i)) break;
            is = i;
            ps = polygon.at(is);
            i++;
        }
    }

    void PelengBase::pelengParamsByPoints(QPointF pb, QPointF pe, qreal &azimuth, qreal &length)
    {
        QPointF from, to;
        from = pb;
        to = pe;

        azimuth = 0;
        length = 0;
        if (from != to)
        {
            // вычисление азимута через вектора и плоскости
            Vector v1, v2;

            v1 = VectorFromSphere(from);
            v2 = VectorFromSphere(to);

            azimuth = rad_deg(CalculateAngle(v1, v2, v1));
            length = lengthByPoints(pb, pe);
        }
    }

    qreal PelengBase::lengthByPoints(QPointF pb, QPointF pe)
    {
        // вычисление расстояния
        qreal p0, pp;

        qreal a1, a2, a3;

        a1 = cos((pe.y() - pb.y()) / 2.0 * M_PI / 180.0);
        a2 = cos(pb.y() * M_PI / 180.0) * cos(pe.y() * M_PI / 180.0);
        a3 = sin((pe.x() - pb.x()) / 2.0 * M_PI / 180.0);
        p0 = sqrt(a1 * a1 - a2 * a3 * a3);

        a1 = sin((pe.y() - pb.y()) / 2.0 * M_PI / 180.0);
        pp = sqrt(a1 * a1 + a2 * a3 * a3);

        return (EARTH_EQUATOR_LENGTH / M_PI) * (M_PI / 2 - atan2(p0, pp)); 
    }

    Vector PelengBase::VectorFromSphere(QPointF p)
    {
        return Vector(
            cos(deg_rad(p.y())) * cos(deg_rad(p.x())),
            cos(deg_rad(p.y())) * sin(deg_rad(p.x())),
            sin(deg_rad(p.y()))
            );
    }

    double PelengBase::CalculateAngle(Vector v1, Vector v2, Vector v)
    {
        // вычисление векторов для системы координат
        Vector oz, s1, s2, s3;
        oz = VectorFromSphere(QPointF(0, 90));
        s1 = v;
        s2 = oz.Vect(s1);
        s3 = s1.Vect(s2);

        // определение плоскостей
        Plane p1(v, v + s2, v + s3);
        Plane p2(v1, v2, Vector());

        // линия пересечения плоскостей (направляющий вектор)
        Vector ln = p1.vector().Vect(p2.vector());

        // угол между s3 и ln
        qreal angle = s3.Angle(ln);

        // исправление угла под азимут
        angle = M_PI - angle;
        Plane pz(v, Vector(), oz);
        if (pz.value(v2) < 0) angle = -angle;

        return angle;
    }



}
