/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_series_data.h"
#include "qwt_math.h"

static inline QRectF qwtBoundingRect( const QPointF &sample )
{
    return QRectF( sample.x(), sample.y(), 0.0, 0.0 );
}

static inline QRectF qwtBoundingRect( const QwtPoint3D &sample )
{
    return QRectF( sample.x(), sample.y(), 0.0, 0.0 );
}

static inline QRectF qwtBoundingRect( const QwtPointPolar &sample )
{
    return QRectF( sample.azimuth(), sample.radius(), 0.0, 0.0 );
}

static inline QRectF qwtBoundingRect( const QwtIntervalSample &sample )
{
    return QRectF( sample.interval.minValue(), sample.value,
        sample.interval.maxValue() - sample.interval.minValue(), 0.0 );
}

static inline QRectF qwtBoundingRect( const QwtSetSample &sample )
{
    if ( sample.set.empty() )
        return QRectF( sample.value, 0.0, 0.0, -1.0 );

    double minY = sample.set[0];
    double maxY = sample.set[0];

    for ( int i = 1; i < sample.set.size(); i++ )
    {
        if ( sample.set[i] < minY )
            minY = sample.set[i];

        if ( sample.set[i] > maxY )
            maxY = sample.set[i];
    }

    return QRectF( sample.value, minY, 0.0, maxY - minY );
}

static inline QRectF qwtBoundingRect( const QwtOHLCSample &sample )
{
    const QwtInterval interval = sample.boundingInterval();
    return QRectF( interval.minValue(), sample.time, interval.width(), 0.0 );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/

template <class T>
QRectF qwtBoundingRectT(
    const QwtSeriesData<T>& series, int from, int to )
{
    QPointF topLeft;
    QPointF bottomRight;
    QRectF boundingRect( 1.0, 1.0, -2.0, -2.0 ); // invalid;

    if ( from < 0 )
        from = 0;

    if ( to < 0 )
        to = series.size() - 1;

    if ( to < from )
        return boundingRect;

    int i;
    bool rectReady = false;
    for (i = from; i <= to; i++)
    {
        const QRectF rect = qwtBoundingRect(series.sample(i));
        if (rect.width() >= 0.0 && rect.height() >= 0.0)
        {
            topLeft = QPointF(rect.left(), rect.top());
            bottomRight = QPointF(rect.right(), rect.bottom());
            i++;
            rectReady = true;
            break;
        }
    }

    for (; i <= to; i++ )
    {
        const QRectF rect = qwtBoundingRect(series.sample(i));

        topLeft.setX(qMin(topLeft.x(), rect.left()));
        topLeft.setY(qMin(topLeft.y(), rect.top()));
        bottomRight.setX(qMax(bottomRight.x(), rect.right()));
        bottomRight.setY(qMax(bottomRight.y(), rect.bottom()));
    }

    if (rectReady)
    {
        boundingRect = QRectF(topLeft, bottomRight);
    }

    return boundingRect;
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QPointF> &series, int from, int to )
{
    return qwtBoundingRectT<QPointF>( series, from, to );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QwtPoint3D> &series, int from, int to )
{
    return qwtBoundingRectT<QwtPoint3D>( series, from, to );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  The horizontal coordinates represent the azimuth, the
  vertical coordinates the radius.

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QwtPointPolar> &series, int from, int to )
{
    return qwtBoundingRectT<QwtPointPolar>( series, from, to );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QwtIntervalSample>& series, int from, int to )
{
    return qwtBoundingRectT<QwtIntervalSample>( series, from, to );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QwtOHLCSample>& series, int from, int to )
{
    return qwtBoundingRectT<QwtOHLCSample>( series, from, to );
}

/*!
  \brief Calculate the bounding rectangle of a series subset

  Slow implementation, that iterates over the series.

  \param series Series
  \param from Index of the first sample, <= 0 means from the beginning
  \param to Index of the last sample, < 0 means to the end

  \return Bounding rectangle
*/
QRectF qwtBoundingRect(
    const QwtSeriesData<QwtSetSample>& series, int from, int to )
{
    return qwtBoundingRectT<QwtSetSample>( series, from, to );
}

/*!
   Constructor
   \param samples Samples
*/
QwtPointSeriesData::QwtPointSeriesData(
        const QVector<QPointF> &samples ):
    QwtArraySeriesData<QPointF>( samples )
{
}

/*!
  \brief Calculate the bounding rectangle

  The bounding rectangle is calculated once by iterating over all
  points and is stored for all following requests.

  \return Bounding rectangle
*/
QRectF QwtPointSeriesData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );

    return d_boundingRect;
}

/*!
   Constructor
   \param samples Samples
*/
QwtPoint3DSeriesData::QwtPoint3DSeriesData(
        const QVector<QwtPoint3D> &samples ):
    QwtArraySeriesData<QwtPoint3D>( samples )
{
}

/*!
  \brief Calculate the bounding rectangle

  The bounding rectangle is calculated once by iterating over all
  points and is stored for all following requests.

  \return Bounding rectangle
*/
QRectF QwtPoint3DSeriesData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );

    return d_boundingRect;
}

/*!
   Constructor
   \param samples Samples
*/
QwtIntervalSeriesData::QwtIntervalSeriesData(
        const QVector<QwtIntervalSample> &samples ):
    QwtArraySeriesData<QwtIntervalSample>( samples )
{
}

/*!
  \brief Calculate the bounding rectangle

  The bounding rectangle is calculated once by iterating over all
  points and is stored for all following requests.

  \return Bounding rectangle
*/
QRectF QwtIntervalSeriesData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );

    return d_boundingRect;
}

/*!
   Constructor
   \param samples Samples
*/
QwtSetSeriesData::QwtSetSeriesData(
        const QVector<QwtSetSample> &samples ):
    QwtArraySeriesData<QwtSetSample>( samples )
{
}

/*!
  \brief Calculate the bounding rectangle

  The bounding rectangle is calculated once by iterating over all
  points and is stored for all following requests.

  \return Bounding rectangle
*/
QRectF QwtSetSeriesData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );

    return d_boundingRect;
}

/*!
   Constructor
   \param samples Samples
*/
QwtTradingChartData::QwtTradingChartData(
        const QVector<QwtOHLCSample> &samples ):
    QwtArraySeriesData<QwtOHLCSample>( samples )
{
}

/*!
  \brief Calculate the bounding rectangle

  The bounding rectangle is calculated once by iterating over all
  points and is stored for all following requests.

  \return Bounding rectangle
*/
QRectF QwtTradingChartData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );

    return d_boundingRect;
}
