#include "rpp.h"
#include "qpen.h"

#include <QBitmap>

#define _USE_MATH_DEFINES
#include "math.h"

#include <QSvgRenderer>
#include <QFile>
#include <QDomDocument>

namespace qmapcontrol
{
    Rpp::Rpp(QString &fileName, QPointF position, qreal azimuth, QString name, QPen pen)
        : Point(position.x(), position.y(), name, Alignment::Middle)
    {
        _fileName = fileName;
        _azimuth = azimuth;
        mypixmap = NULL;
        size = QSize(15, 20);

        mypen = pen;

        updatePixmap();
    }

    Rpp::Rpp(QPixmap &pixmap, QPointF position, qreal azimuth, QString name, QPen pen)
        : Point(position.x(), position.y(), name, Alignment::Middle)
    {
        mypixmap = new QPixmap(pixmap);
        _azimuth = azimuth;
        size = pixmap.size();
        displaysize = size;

        mypen = pen;
    }

    Rpp::~Rpp()
    {
    }

    void Rpp::setAzimuth(const qreal &azimuth)
    {
        _azimuth = azimuth;

    }

    qreal Rpp::azimuth()
    {
        return _azimuth;
    }

    void Rpp::accept(GeometryVisitor *visitor)
    {
        visitor->visit(this);
    }

    void Rpp::setPen(QPen pen)
    {
        mypen = pen;
    }

    void    Rpp::updatePixmap()
    {
        if (_fileName.isEmpty()) return;

        if (mypixmap) delete mypixmap;

        QPixmap pm;
        if (!_fileName.toLower().endsWith("svg"))
        {
            QPixmap mask(_fileName);
            if (mask.isNull()) return;
            size = mask.size();
            QBitmap msk = mask.createMaskFromColor(QColor(255, 255, 255).rgb(), Qt::MaskInColor);

            pm = QPixmap(mask.width(), mask.height());
            pm.fill(Qt::transparent);
            pm.setMask(msk);
            QPainter painter(&pm);
            painter.setCompositionMode(QPainter::CompositionMode_Multiply);
            painter.drawPixmap(0, 0, msk);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(0, 0, msk.width(), msk.height(), mypen.color());
            painter.end();

        }
        else
        {
            // производим загрузку SVG-файла в виде XML-документа
            // заменяем все упоминания атрибута color на нужный нам цвет
            QByteArray svg;
            QFile xmlFile(_fileName);
            if (xmlFile.open(QIODevice::ReadOnly))
            {
                QDomDocument doc;
                if (doc.setContent(&xmlFile))
                {
                    replaceColorAttribute_(doc, mypen.color());
                }
                xmlFile.close();

                svg = doc.toByteArray();
            }

            pm = QPixmap(QSize(32, 32));
            size = pm.size();
            pm.fill(Qt::transparent);
            QSvgRenderer r(svg);
            QPainter painter(&pm);

            painter.translate(pm.width() / 2, pm.height() / 2);
            painter.rotate(_azimuth);
            painter.translate(-pm.width() / 2, -pm.height() / 2);

            r.render(&painter);
            painter.end();
        }

        mypixmap = new QPixmap(pm);
    }

    void Rpp::replaceColorAttribute_(QDomNode &node, QColor color)
    {
        static QString attrColor("stroke");
        static QString elemStyle("style");
        static QRegExp replaceStroke("stroke:#[\\dabcdefABCDEF]{6}");

#if QT_VERSION >= 0x050200
        QString newStroke = QString::fromLatin1("#%1%2%3%4")
            .arg(color.alpha(), 2, 16, QLatin1Char('0'))
            .arg(color.red(), 2, 16, QLatin1Char('0'))
            .arg(color.green(), 2, 16, QLatin1Char('0'))
            .arg(color.blue(), 2, 16, QLatin1Char('0'));
#else
        QString newStroke = QString::fromLatin1("#%1%2%3")
            .arg(color.red(), 2, 16, QLatin1Char('0'))
            .arg(color.green(), 2, 16, QLatin1Char('0'))
            .arg(color.blue(), 2, 16, QLatin1Char('0'));
#endif

        QDomNodeList dnl = node.childNodes();
        for (int i = 0; i < dnl.count(); ++i)
        {
            QDomElement item = dnl.at(i).toElement();
            if (item.hasAttribute(attrColor))
            {
                QDomElement newItem = item;
                newItem.setAttribute(attrColor, newStroke);
                node.replaceChild(newItem, item);
            }
            else if (item.nodeName().compare(elemStyle) == 0 && item.hasChildNodes())
            {
                QDomCDATASection dataSection = item.firstChild().toCDATASection();
                QString data = dataSection.data();
                data.replace(replaceStroke, "stroke:" + newStroke);
                dataSection.setData(data);
            }

            //replaceColorAttribute_(dnl.item(i), color);
        }
    }

    void Rpp::draw(QPainter* painter, const MapAdapter* mapadapter, const QRectF &viewport, const QPoint offset)
    {
        if (!visible)
            return;

        if (homelevel > 0)
        {

            int currentzoom = mapadapter->maxZoom() < mapadapter->minZoom() ? mapadapter->minZoom() - mapadapter->currentZoom() : mapadapter->currentZoom();

            int diffzoom = homelevel - currentzoom;
            int viewheight = size.height();
            int viewwidth = size.width();
            viewheight = int(viewheight / pow(2, diffzoom));
            viewwidth = int(viewwidth / pow(2, diffzoom));

            if (minsize.height() != -1 && viewheight < minsize.height())
                viewheight = minsize.height();
            else if (maxsize.height() != -1 && viewheight > maxsize.height())
                viewheight = maxsize.height();


            if (minsize.width() != -1 && viewwidth < minsize.width())
                viewwidth = minsize.width();
            else if (maxsize.width() != -1 && viewwidth > maxsize.width())
                viewwidth = maxsize.width();


            displaysize = QSize(viewwidth, viewheight);
        }
        else
        {
            displaysize = size;
        }


        if (mypixmap != 0)
        {
            const QPointF c = QPointF(X, Y);
            QPoint point = mapadapter->coordinateToDisplay(c);
            if (!_fileName.toLower().endsWith("svg"))
            {
                QTransform origTransform = painter->transform();



                QPoint alignedtopleft = alignedPoint(point);

                painter->translate(alignedtopleft.x() + displaysize.width() / 2, alignedtopleft.y() + displaysize.height() / 2);
                painter->rotate(_azimuth);
                painter->translate(-(alignedtopleft.x() + displaysize.width() / 2), -(alignedtopleft.y() + displaysize.height() / 2));

                painter->drawPixmap(alignedtopleft.x(), alignedtopleft.y(), displaysize.width(), displaysize.height(), *mypixmap);

                painter->setTransform(origTransform);

            }
            else
            {
                QPoint alignedtopleft = alignedPoint(point);
                painter->drawPixmap(alignedtopleft.x(), alignedtopleft.y(), displaysize.width(), displaysize.height(), *mypixmap);
            }

        }
        else if (mywidget != 0)
        {
            drawWidget(mapadapter, offset);
        }

    }

}
