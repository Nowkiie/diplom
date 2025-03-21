#ifndef PELENGBASE_H
#define PELENGBASE_H
#include <cmath>
#include <QPolygon>
#include <QPoint>
#include <QList>

#define EARTH_EQUATOR_LENGTH 40075.0
#define PELENG_DELTA_MULT 3.0//10.0

namespace qmapcontrol
{
    class Quaternion;
    class Vector;

    /*!
    *    Класс для расчета параметров пеленга
    *    @author Maxim Poylov
    */
    class PelengBase
    {
    public:
        static void calculate(QPointF position, qreal azimuth, qreal length, QPolygonF &peleng);
        static void calculate(QPointF position, qreal azimuth, qreal length, qreal deltaMultiplier, QPolygonF &peleng);
        static void calculateEndPoint(QPointF position, qreal azimuth, qreal length, QPointF &end);

        static void splitByMapBorders(QPolygonF &peleng, QList<QPolygonF*> &splittedPeleng);
    
        static void optimizePolygon(QPolygonF &polygon);
    
        static qreal f(QPointF pb, QPointF pe, qreal x);
        static qreal x(QPointF pb, QPointF pe, qreal y);

        static void pelengParamsByPoints(QPointF pb, QPointF pe, qreal &azimuth, qreal &length);
        static qreal lengthByPoints(QPointF pb, QPointF pe);

    private:
        PelengBase() = delete;
        PelengBase(const PelengBase&) = delete;
        PelengBase operator = (const PelengBase&) = delete;

        static void _getBaseQuats(qreal angX, qreal angY, qreal angK, Quaternion &q);

        static void _splitVerticiesByBorders(QPolygonF *vert, QList<QPolygonF*> *polygons);

        static qreal deg_rad(qreal x);
        static qreal rad_deg(qreal x);

        static Vector VectorFromSphere(QPointF p);
        static double CalculateAngle(Vector v1, Vector v2, Vector v);

        static QPointF borderedPoint(QPointF p);

    };

    /*!
    *    Структура для реализации операций с кватернионами
    *    @author Maxim Poylov
    */
    class Quaternion
    {
    public:
        Quaternion(qreal r, qreal i, qreal j, qreal k)
        {
            this->r = r;
            this->i = i;
            this->j = j;
            this->k = k;
        }

        ~Quaternion() {};

    public:
        qreal r, i, j, k;

        double length() const
        {
            return std::sqrt(r * r + i * i + j * j + k * k);
        }

        Quaternion inverse() const
        {
            double length = this->length();
            return Quaternion(r / length, -i / length, -j / length, -k / length);
        }

        Quaternion unit() const
        {
            double length = this->length();
            return Quaternion(r, i / length, j / length, k / length);
        }

        Quaternion mul(const Quaternion &q) const
        {
            qreal r = this->r * q.r - this->i * q.i - this->j * q.j - this->k * q.k;
            qreal i = this->r * q.i + this->i * q.r + this->j * q.k - this->k * q.j;
            qreal j = this->r * q.j - this->i * q.k + this->j * q.r + this->k * q.i;
            qreal k = this->r * q.k + this->i * q.j - this->j * q.i + this->k * q.r;
            return Quaternion(r, i, j, k);
        }

        Quaternion vect(const Quaternion &q) const
        {
            qreal r = 0;
            qreal i = this->j * q.k - this->k * q.j;
            qreal j = this->k * q.i - this->i * q.k;
            qreal k = this->i * q.j - this->j * q.i;
            return Quaternion(r, i, j, k);
        }

        Quaternion operator- (const Quaternion &q) const
        {
            return Quaternion(r - q.r, i - q.i, j - q.j, k - q.k);
        }
    };


    /*!
    *    Структура для реализации операций с векторами
    *    @author Maxim Poylov
    */
    class Vector
    {
    public:
        Vector()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        Vector(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        double X;
        double Y;
        double Z;

        Vector Vect(const Vector &v) const
        {
            return Vector(
                Y * v.Z - Z * v.Y,
                Z * v.X - X * v.Z,
                X * v.Y - Y * v.X);
        }

        double Scalar(const Vector &v) const
        {
            return X * v.X + Y * v.Y + Z * v.Z;
        }

        double Length() const
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }

        Vector operator-(const Vector &v) const
        {
            return Vector(
                X - v.X,
                Y - v.Y,
                Z - v.Z
                );
        }
        Vector operator+(Vector v) const
        {
            return Vector(
                X + v.X,
                Y + v.Y,
                Z + v.Z
                );
        }
        bool operator==(const Vector &v) const
        {
            return (X == v.X) && (Y == v.Y) && (Z - v.Z);
        }
        bool operator!=(const Vector &v) const
        {
            return !(*this == v);
        }


        double Angle(const Vector &v) const
        {
            double cos = this->Scalar(v) / (this->Length() * v.Length());
            if (cos > 1) cos = 1;
            else if (cos < -1) cos = -1;
            return acos(cos);
        }
    };

    /*!
    *    Структура для реализации операций с плоскостями
    *    @author Maxim Poylov
    */
    class Plane
    {
        qreal A, B, C, D;

    public:
        Plane()
        {
            this->A = 0;
            this->B = 0;
            this->C = 0;
            this->D = 0;
        }

        Plane(qreal a, qreal b, qreal c, qreal d)
        {
            this->A = a;
            this->B = b;
            this->C = c;
            this->D = d;
        }

        Plane(Vector p0, Vector p1, Vector p2)
        {
            p1 = p1 - p0;
            p2 = p2 - p0;

            A = p1.Y * p2.Z - p1.Z * p2.Y;
            B = p1.Z * p2.X - p1.X * p2.Z;
            C = p1.X * p2.Y - p1.Y * p2.X;
            D = -p0.X * A - p0.Y * B - p0.Z * C;

            if (p1 != p2)
            {
                double n = sqrt(A * A + B * B + C * C); // *(D > 0 ? -1 : 1);
                A /= n;
                B /= n;
                C /= n;
                D /= n;
            }
        }

        ~Plane() {};

        Plane norm() const
        {
            qreal n = sqrt(A * A + B * B + C * C); // *(D > 0 ? -1 : 1);
            return Plane(A / n, B / n, C / n, D / n);
        }

        double value(const Vector &v) const
        {
            return A * v.X + B * v.Y + C * v.Z + D;
        }

        Vector vector() const
        {
            return Vector(A, B, C);
        }
    };
}
#endif //PELENGBASE_H
