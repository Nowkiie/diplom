#include "topographySeries.h"
#include <math.h>
#include <qpainter.h>

using namespace QtDataVisualization;

TopographySeries::TopographySeries()
{
    converter = std::make_unique<converter_toHeight>();
    setDrawMode(QSurface3DSeries::DrawSurface);
    setFlatShadingEnabled(true);
    setBaseColor(Qt::white);
    dataArray = new QSurfaceDataArray;
}

TopographySeries::~TopographySeries() {}

void TopographySeries::clearSeries()
{
    dataArray->clear();
}

int TopographySeries::calcHeightForCurrentPoint(QPointF coordPoint,
                                                QPointF startCoord,
                                                QImage combinedImage,
                                                double stepX, double stepZ)
{
    float coordPx_x = (coordPoint.x() - startCoord.x()) / stepZ;
    float coordPx_y = (coordPoint.y() - startCoord.y()) / stepX;

    QColor color(
        combinedImage.pixel(coordPx_x, combinedImage.height() - coordPx_y));
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int height = converter->convert(red, green, blue);

    return height;
}

void TopographySeries::setSeriesPoint(float diffLon, float diffLat,
                                      float coordX, float coordZ,
                                      QImage combinedImage, float startCoordZ,
                                      float startCoordX)
{
    int imageHeight = combinedImage.height();
    int imageWidth = combinedImage.width();
    //int imageWidth = 256 * diff_x;

    //combinedImage.save("test.jpg", "JPEG");

    double stepX = diffLat / imageHeight;
    double stepZ = diffLon / imageWidth;

    dataArray->reserve(10);

    for (int i = 0; i < 10; i++)
    {
        float z = float(i) * stepZ + coordZ;

        QSurfaceDataRow* newRow = new QSurfaceDataRow(10);
        for (int j = 0; j < 10; j++)
        {
            float x = float(j) * stepX + coordX;

            float y =
                calcHeightForCurrentPoint({z, x}, {startCoordZ, startCoordX},
                                          combinedImage, stepX, stepZ);

            (*newRow)[j].setPosition(QVector3D(x, y, z));
        }

        *dataArray << newRow;
    }

    dataProxy()->resetArray(dataArray);

    //

    //delete dataArray;
    //! [1]

    m_sampleCountX = float(imageWidth);
    m_sampleCountZ = float(imageHeight);
}

void TopographySeries::setTopograhySeries(float diffLon, float diffLat,
                                          float startCoordX, float startCoordZ,
                                          QImage combinedImage)
{
    //int imageHeight = 256 * diff_y;
    int imageHeight = combinedImage.height();
    int imageWidth = combinedImage.width();
    //int imageWidth = 256 * diff_x;

    // combinedImage.save("test.jpg", "JPEG");

    double stepX = diffLat / imageHeight;
    double stepZ = diffLon / imageWidth;

    dataArray->reserve(imageWidth);

    for (int i = 0; i < imageWidth; i++)
    {
        float z = float(i) * stepZ + startCoordZ;

        QSurfaceDataRow* newRow = new QSurfaceDataRow(imageHeight);
        for (int j = 0; j < imageHeight; j++)
        {
            QColor color(combinedImage.pixel(i, imageHeight - j));
            int red = color.red();
            int green = color.green();
            int blue = color.blue();
            int height = converter->convert(red, green, blue);
            float y = height;

            (*newRow)[j].setPosition(
                QVector3D(float(j) * stepX + startCoordX, y, z));
        }

        *dataArray << newRow;
    }

    dataProxy()->resetArray(dataArray);

    //

    //delete dataArray;
    //! [1]

    m_sampleCountX = float(imageWidth);
    m_sampleCountZ = float(imageHeight);
}
