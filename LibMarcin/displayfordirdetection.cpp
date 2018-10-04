
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "dirdetectionparams.h"

#include "displayfordirdetection.h"

#define PI 3.14159265

using namespace cv;
void DrawTilesOnImage(cv::Mat ImIn, DirDetectionParams params)
{
    DrawTilesOnImage(ImIn, params.showTilesOnImage, params.tileShape, params.tileOffsetX, params.tileOffsetY,
                     params.tileSize, params.tileShift, params.tileLineWidth);
}
//-----------------------------------------------------------------------------------------------
void DrawTilesOnImage(cv::Mat ImIn, bool showTilesOnImage, int tileShape, int tileOffsetX, int tileOffsetY,
                      int tileSize, int tileShift, int tileLineWidth)
{
    if(!showTilesOnImage)
        return;
    if(ImIn.empty())
        return;
    int maxX = ImIn.cols;
    int maxY = ImIn.rows;

    if(!maxY || !maxY)
        return;

    int firstTileY = tileOffsetY;
    int lastTileY = maxY - tileSize / 2;
    int firstTileX = tileOffsetX;
    int lastTileX = maxX - tileSize / 2;

    switch (tileShape)
    {
    case 1:
        {
            int tileRadius = tileSize / 2 ;
            for (int y = firstTileY; y < lastTileY; y += tileShift)
            {
                for (int x = firstTileX; x < lastTileX; x += tileShift)
                {
                    ellipse(ImIn, Point(x, y),
                        Size(tileRadius, tileRadius), 0.0, 0.0, 360.0,
                        Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                }
            }
        }
        break;
    case 2:
        {
            int edgeLength = tileSize/2;
            int octagonHalfHeight = (int)((float)edgeLength * 0.8660254);
            for (int y = firstTileY; y < lastTileY; y += tileShift)
            {
                for (int x = firstTileX; x < lastTileX; x += tileShift)
                {

                    Point vertice0(x - edgeLength / 2, y - octagonHalfHeight);
                    Point vertice1(x + edgeLength - edgeLength / 2, y - octagonHalfHeight);
                    Point vertice2(x + edgeLength, y);
                    Point vertice3(x + edgeLength - edgeLength / 2, y + octagonHalfHeight);
                    Point vertice4(x - edgeLength / 2, y + octagonHalfHeight);
                    Point vertice5(x - edgeLength, y);

                    line(ImIn, vertice0, vertice1, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                    line(ImIn, vertice1, vertice2, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                    line(ImIn, vertice2, vertice3, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                    line(ImIn, vertice3, vertice4, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                    line(ImIn, vertice4, vertice5, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                    line(ImIn, vertice5, vertice0, Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                }
            }
        }
        break;
    default:
        {
            int tileLeftTopBorderOffset = tileSize / 2 ;
            int tileRigthBottomBorderOffset =  tileSize - tileSize / 2 - 1 ;
            for (int y = firstTileY; y < lastTileY; y += tileShift)
            {
                for (int x = firstTileX; x < lastTileX; x += tileShift)
                {
                    rectangle(ImIn, Point(x - tileLeftTopBorderOffset, y - tileLeftTopBorderOffset),
                        Point(x + tileRigthBottomBorderOffset, y + tileRigthBottomBorderOffset),
                        Scalar(0.0, 0.0, 0.0, 0.0), tileLineWidth);
                }
            }
        }
        break;
    }

}
//-----------------------------------------------------------------------------------------------
void ShowDirection(Mat ImToShow, int y, int x, float direction, int lineWidth, int lineLength, double scale)
{
    int lineOffsetX = (int)round(lineLength * 0.5 *  sin((double)direction* PI / 180.0));
    int lineOffsetY = (int)round(lineLength * 0.5 * cos((double)direction* PI / 180.0));

    line(ImToShow, Point(x - lineOffsetX, y - lineOffsetY), Point(x + lineOffsetX, y + lineOffsetY), Scalar(0, 0.0, 0.0, 0.0), lineWidth);
    Mat ImToShowTemp;
    if (scale !=1.0)
        cv::resize(ImToShow,ImToShowTemp,Size(),scale,scale,INTER_NEAREST);
    else
        ImToShowTemp = ImToShow;
    imshow("ImOut", ImToShowTemp);
}
//-----------------------------------------------------------------------------------------------
