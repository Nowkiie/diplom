﻿/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_spectrogram.h"
#include "qwt_painter.h"
#include "qwt_interval.h"
#include "qwt_scale_map.h"
#include "qwt_color_map.h"
#include <qimage.h>
#include <qpen.h>
#include <qpainter.h>
#include <qmath.h>
#include <qalgorithms.h>
#if QT_VERSION >= 0x040400
#include <qthread.h>
#ifndef QT_NO_QFUTURE
#include <qfuture.h>
#include <qtconcurrentrun.h>
#endif
#endif

#define DEBUG_RENDER 0

#if DEBUG_RENDER
#include <QElapsedTimer>
#endif

class QwtPlotSpectrogram::PrivateData
{
public:
    PrivateData():
        data( NULL )
    {
        colorMap = new QwtLinearColorMap();
        displayMode = ImageMode;

        conrecFlags = QwtRasterData::IgnoreAllVerticesOnLevel;
#if 0
        conrecFlags |= QwtRasterData::IgnoreOutOfRange;
#endif
    }
    ~PrivateData()
    {
        delete data;
        delete colorMap;
    }

    QwtRasterData *data;
    QwtColorMap *colorMap;
    DisplayModes displayMode;

    QList<double> contourLevels;
    QPen defaultContourPen;
    QwtRasterData::ConrecFlags conrecFlags;
};

/*!
   Sets the following item attributes:
   - QwtPlotItem::AutoScale: true
   - QwtPlotItem::Legend:    false

   The z value is initialized by 8.0.

   \param title Title

   \sa QwtPlotItem::setItemAttribute(), QwtPlotItem::setZ()
*/
QwtPlotSpectrogram::QwtPlotSpectrogram( const QString &title ):
    QwtPlotRasterItem( title )
{
    d_data = new PrivateData();

    setItemAttribute( QwtPlotItem::AutoScale, true );
    setItemAttribute( QwtPlotItem::Legend, false );

    setZ( 8.0 );
}

//! Destructor
QwtPlotSpectrogram::~QwtPlotSpectrogram()
{
    delete d_data;
}

//! \return QwtPlotItem::Rtti_PlotSpectrogram
int QwtPlotSpectrogram::rtti() const
{
    return QwtPlotItem::Rtti_PlotSpectrogram;
}

/*!
   The display mode controls how the raster data will be represented.

   \param mode Display mode
   \param on On/Off

   The default setting enables ImageMode.

   \sa DisplayMode, displayMode()
*/
void QwtPlotSpectrogram::setDisplayMode( DisplayMode mode, bool on )
{
    if ( on != bool( mode & d_data->displayMode ) )
    {
        if ( on )
            d_data->displayMode |= mode;
        else
            d_data->displayMode &= ~mode;
    }

    legendChanged();
    itemChanged();
}

/*!
   The display mode controls how the raster data will be represented.

   \param mode Display mode
   \return true if mode is enabled
*/
bool QwtPlotSpectrogram::testDisplayMode( DisplayMode mode ) const
{
    return ( d_data->displayMode & mode );
}

/*!
  Change the color map

  Often it is useful to display the mapping between intensities and
  colors as an additional plot axis, showing a color bar.

  \param colorMap Color Map

  \sa colorMap(), QwtScaleWidget::setColorBarEnabled(),
      QwtScaleWidget::setColorMap()
*/
void QwtPlotSpectrogram::setColorMap( QwtColorMap *colorMap )
{
    if ( d_data->colorMap != colorMap )
    {
        delete d_data->colorMap;
        d_data->colorMap = colorMap;
    }

    invalidateCache();

    legendChanged();
    itemChanged();
}

/*!
   \return Color Map used for mapping the intensity values to colors
   \sa setColorMap()
*/
const QwtColorMap *QwtPlotSpectrogram::colorMap() const
{
    return d_data->colorMap;
}

/*!
  Build and assign the default pen for the contour lines

  In Qt5 the default pen width is 1.0 ( 0.0 in Qt4 ) what makes it
  non cosmetic ( see QPen::isCosmetic() ). This method has been introduced
  to hide this incompatibility.

  \param color Pen color
  \param width Pen width
  \param style Pen style

  \sa pen(), brush()
 */
void QwtPlotSpectrogram::setDefaultContourPen(
    const QColor &color, qreal width, Qt::PenStyle style )
{
    setDefaultContourPen( QPen( color, width, style ) );
}

/*!
   \brief Set the default pen for the contour lines

   If the spectrogram has a valid default contour pen
   a contour line is painted using the default contour pen.
   Otherwise (pen.style() == Qt::NoPen) the pen is calculated
   for each contour level using contourPen().

   \sa defaultContourPen(), contourPen()
*/
void QwtPlotSpectrogram::setDefaultContourPen( const QPen &pen )
{
    if ( pen != d_data->defaultContourPen )
    {
        d_data->defaultContourPen = pen;

        legendChanged();
        itemChanged();
    }
}

/*!
   \return Default contour pen
   \sa setDefaultContourPen()
*/
QPen QwtPlotSpectrogram::defaultContourPen() const
{
    return d_data->defaultContourPen;
}

/*!
   \brief Calculate the pen for a contour line

   The color of the pen is the color for level calculated by the color map

   \param level Contour level
   \return Pen for the contour line
   \note contourPen is only used if defaultContourPen().style() == Qt::NoPen

   \sa setDefaultContourPen(), setColorMap(), setContourLevels()
*/
QPen QwtPlotSpectrogram::contourPen( double level ) const
{
    if ( d_data->data == NULL || d_data->colorMap == NULL )
        return QPen();

    const QwtInterval intensityRange = d_data->data->interval(Qt::ZAxis);
    const QColor c( d_data->colorMap->rgb( intensityRange, level ) );

    return QPen( c );
}

/*!
   Modify an attribute of the CONREC algorithm, used to calculate
   the contour lines.

   \param flag CONREC flag
   \param on On/Off

   \sa testConrecFlag(), renderContourLines(),
       QwtRasterData::contourLines()
*/
void QwtPlotSpectrogram::setConrecFlag(
    QwtRasterData::ConrecFlag flag, bool on )
{
    if ( bool( d_data->conrecFlags & flag ) == on )
        return;

    if ( on )
        d_data->conrecFlags |= flag;
    else
        d_data->conrecFlags &= ~flag;

    itemChanged();
}

/*!
   Test an attribute of the CONREC algorithm, used to calculate
   the contour lines.

   \param flag CONREC flag
   \return true, is enabled

   The default setting enables QwtRasterData::IgnoreAllVerticesOnLevel

   \sa setConrecClag(), renderContourLines(),
       QwtRasterData::contourLines()
*/
bool QwtPlotSpectrogram::testConrecFlag(
    QwtRasterData::ConrecFlag flag ) const
{
    return d_data->conrecFlags & flag;
}

/*!
   Set the levels of the contour lines

   \param levels Values of the contour levels
   \sa contourLevels(), renderContourLines(),
       QwtRasterData::contourLines()

   \note contourLevels returns the same levels but sorted.
*/
void QwtPlotSpectrogram::setContourLevels( const QList<double> &levels )
{
    d_data->contourLevels = levels;
    qSort( d_data->contourLevels );

    legendChanged();
    itemChanged();
}

/*!
   \return Levels of the contour lines.

   The levels are sorted in increasing order.

   \sa contourLevels(), renderContourLines(),
       QwtRasterData::contourLines()
*/
QList<double> QwtPlotSpectrogram::contourLevels() const
{
    return d_data->contourLevels;
}

/*!
  Set the data to be displayed

  \param data Spectrogram Data
  \sa data()
*/
void QwtPlotSpectrogram::setData( QwtRasterData *data )
{
    if ( data != d_data->data )
    {
        delete d_data->data;
        d_data->data = data;

        invalidateCache();
        itemChanged();
    }
}

/*!
  \return Spectrogram data
  \sa setData()
*/
const QwtRasterData *QwtPlotSpectrogram::data() const
{
    return d_data->data;
}

/*!
  \return Spectrogram data
  \sa setData()
*/
QwtRasterData *QwtPlotSpectrogram::data()
{
    return d_data->data;
}

/*!
   \return Bounding interval for an axis

   The default implementation returns the interval of the
   associated raster data object.

   \param axis X, Y, or Z axis
   \sa QwtRasterData::interval()
*/
QwtInterval QwtPlotSpectrogram::interval(Qt::Axis axis) const
{
    if ( d_data->data == NULL )
        return QwtInterval();

    return d_data->data->interval( axis );
}

/*!
   \brief Pixel hint

   The geometry of a pixel is used to calculated the resolution and
   alignment of the rendered image.

   The default implementation returns data()->pixelHint( rect );

   \param area In most implementations the resolution of the data doesn't
               depend on the requested area.

   \return Bounding rectangle of a pixel

   \sa QwtPlotRasterItem::pixelHint(), QwtRasterData::pixelHint(),
       render(), renderImage()
*/
QRectF QwtPlotSpectrogram::pixelHint( const QRectF &area ) const
{
    if ( d_data->data == NULL )
        return QRectF();

    return d_data->data->pixelHint( area );
}

/*!
   \brief Render an image from data and color map.

   For each pixel of area the value is mapped into a color.

  \param xMap X-Scale Map
  \param yMap Y-Scale Map
  \param area Requested area for the image in scale coordinates
  \param imageSize Size of the requested image

   \return A QImage::Format_Indexed8 or QImage::Format_ARGB32 depending
           on the color map.

   \sa QwtRasterData::value(), QwtColorMap::rgb(),
       QwtColorMap::colorIndex()
*/
QImage QwtPlotSpectrogram::renderImage(
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &area, const QSize &imageSize ) const
{
    if ( imageSize.isEmpty() || d_data->data == NULL
        || d_data->colorMap == NULL )
    {
        return QImage();
    }

    const QwtInterval intensityRange = d_data->data->interval( Qt::ZAxis );
    if ( !intensityRange.isValid() )
        return QImage();

    QImage::Format format = ( d_data->colorMap->format() == QwtColorMap::RGB )
        ? QImage::Format_ARGB32 : QImage::Format_Indexed8;

    QImage image( imageSize, format );

    if ( d_data->colorMap->format() == QwtColorMap::Indexed )
        image.setColorTable( d_data->colorMap->colorTable( intensityRange ) );

    d_data->data->initRaster( area, image.size() );

#if DEBUG_RENDER
    QElapsedTimer time;
    time.start();
#endif

#if QT_VERSION >= 0x040400 && !defined(QT_NO_QFUTURE)
    uint numThreads = renderThreadCount();

    if ( numThreads <= 0 )
        numThreads = QThread::idealThreadCount();

    if ( numThreads <= 0 )
        numThreads = 1;

    const int numRows = imageSize.height() / numThreads;

    QList< QFuture<void> > futures;
    for ( uint i = 0; i < numThreads; i++ )
    {
        QRect tile( 0, i * numRows, image.width(), numRows );
        if ( i == numThreads - 1 )
        {
            tile.setHeight( image.height() - i * numRows );
            renderTile( xMap, yMap, tile, &image );
        }
        else
        {
            futures += QtConcurrent::run(
                this, &QwtPlotSpectrogram::renderTile,
                xMap, yMap, tile, &image );
        }
    }
    for ( int i = 0; i < futures.size(); i++ )
        futures[i].waitForFinished();

#else // QT_VERSION < 0x040400
    const QRect tile( 0, 0, image.width(), image.height() );
    renderTile( xMap, yMap, tile, &image );
#endif

#if DEBUG_RENDER
    const qint64 elapsed = time.elapsed();
    qDebug() << "renderImage" << imageSize << elapsed;
#endif

    d_data->data->discardRaster();

    return image;
}

/*!
    \brief Render a tile of an image.

    Rendering in tiles can be used to composite an image in parallel
    threads.

    \param xMap X-Scale Map
    \param yMap Y-Scale Map
    \param tile Geometry of the tile in image coordinates
    \param image Image to be rendered
*/
void QwtPlotSpectrogram::renderTile(
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRect &tile, QImage *image ) const
{
    const QwtInterval range = d_data->data->interval( Qt::ZAxis );
    if ( !range.isValid() )
        return;

    if ( d_data->colorMap->format() == QwtColorMap::RGB )
    {
        for ( int y = tile.top(); y <= tile.bottom(); y++ )
        {
            const double ty = yMap.invTransform( y );

            QRgb *line = reinterpret_cast<QRgb *>( image->scanLine( y ) );
            line += tile.left();

            for ( int x = tile.left(); x <= tile.right(); x++ )
            {
                const double tx = xMap.invTransform( x );

                *line++ = d_data->colorMap->rgb( range,
                    d_data->data->value( tx, ty ) );
            }
        }
    }
    else if ( d_data->colorMap->format() == QwtColorMap::Indexed )
    {
        for ( int y = tile.top(); y <= tile.bottom(); y++ )
        {
            const double ty = yMap.invTransform( y );

            unsigned char *line = image->scanLine( y );
            line += tile.left();

            for ( int x = tile.left(); x <= tile.right(); x++ )
            {
                const double tx = xMap.invTransform( x );

                *line++ = d_data->colorMap->colorIndex( range,
                    d_data->data->value( tx, ty ) );
            }
        }
    }
}

/*!
   \brief Return the raster to be used by the CONREC contour algorithm.

   A larger size will improve the precision of the CONREC algorithm,
   but will slow down the time that is needed to calculate the lines.

   The default implementation returns rect.size() / 2 bounded to
   the resolution depending on pixelSize().

   \param area Rectangle, where to calculate the contour lines
   \param rect Rectangle in pixel coordinates, where to paint the contour lines
   \return Raster to be used by the CONREC contour algorithm.

   \note The size will be bounded to rect.size().

   \sa drawContourLines(), QwtRasterData::contourLines()
*/
QSize QwtPlotSpectrogram::contourRasterSize(
    const QRectF &area, const QRect &rect ) const
{
    QSize raster = rect.size() / 2;

    const QRectF pixelRect = pixelHint( area );
    if ( !pixelRect.isEmpty() )
    {
        const QSize res( qCeil( rect.width() / pixelRect.width() ),
            qCeil( rect.height() / pixelRect.height() ) );
        raster = raster.boundedTo( res );
    }

    return raster;
}

/*!
   Calculate contour lines

   \param rect Rectangle, where to calculate the contour lines
   \param raster Raster, used by the CONREC algorithm
   \return Calculated contour lines

   \sa contourLevels(), setConrecFlag(),
       QwtRasterData::contourLines()
*/
QwtRasterData::ContourLines QwtPlotSpectrogram::renderContourLines(
    const QRectF &rect, const QSize &raster ) const
{
    if ( d_data->data == NULL )
        return QwtRasterData::ContourLines();

    return d_data->data->contourLines( rect, raster,
        d_data->contourLevels, d_data->conrecFlags );
}

/*!
   Paint the contour lines

   \param painter Painter
   \param xMap Maps x-values into pixel coordinates.
   \param yMap Maps y-values into pixel coordinates.
   \param contourLines Contour lines

   \sa renderContourLines(), defaultContourPen(), contourPen()
*/
void QwtPlotSpectrogram::drawContourLines( QPainter *painter,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QwtRasterData::ContourLines &contourLines ) const
{
    if ( d_data->data == NULL )
        return;

    const int numLevels = d_data->contourLevels.size();
    for ( int l = 0; l < numLevels; l++ )
    {
        const double level = d_data->contourLevels[l];

        QPen pen = defaultContourPen();
        if ( pen.style() == Qt::NoPen )
            pen = contourPen( level );

        if ( pen.style() == Qt::NoPen )
            continue;

        painter->setPen( pen );

        const QPolygonF &lines = contourLines[level];
        for ( int i = 0; i < lines.size(); i += 2 )
        {
            const QPointF p1( xMap.transform( lines[i].x() ),
                yMap.transform( lines[i].y() ) );
            const QPointF p2( xMap.transform( lines[i+1].x() ),
                yMap.transform( lines[i+1].y() ) );

            QwtPainter::drawLine( painter, p1, p2 );
        }
    }
}

/*!
  \brief Draw the spectrogram

  \param painter Painter
  \param xMap Maps x-values into pixel coordinates.
  \param yMap Maps y-values into pixel coordinates.
  \param canvasRect Contents rectangle of the canvas in painter coordinates

  \sa setDisplayMode(), renderImage(),
      QwtPlotRasterItem::draw(), drawContourLines()
*/
void QwtPlotSpectrogram::draw( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &canvasRect ) const
{
    if ( d_data->displayMode & ImageMode )
        QwtPlotRasterItem::draw( painter, xMap, yMap, canvasRect );

    if ( d_data->displayMode & ContourMode )
    {
        // Add some pixels at the borders
        const int margin = 2;
        QRectF rasterRect( canvasRect.x() - margin, canvasRect.y() - margin,
            canvasRect.width() + 2 * margin, canvasRect.height() + 2 * margin );

        QRectF area = QwtScaleMap::invTransform( xMap, yMap, rasterRect );

        const QRectF br = boundingRect();
        if ( br.isValid() )
        {
            area &= br;
            if ( area.isEmpty() )
                return;

            rasterRect = QwtScaleMap::transform( xMap, yMap, area );
        }

        QSize raster = contourRasterSize( area, rasterRect.toRect() );
        raster = raster.boundedTo( rasterRect.toRect().size() );
        if ( raster.isValid() )
        {
            const QwtRasterData::ContourLines lines =
                renderContourLines( area, raster );

            drawContourLines( painter, xMap, yMap, lines );
        }
    }
}
