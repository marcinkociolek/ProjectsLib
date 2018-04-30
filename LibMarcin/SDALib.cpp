#include <opencv2/core.hpp>
#include "RegionU16Lib.h"
#include "SDALib.h"

using namespace cv;

//--------------------------------------------------------------------------------------------------
cv::Mat CalculateSDAL(cv::Mat ImIn, cv::Mat Roi, int radius, int *outSDARoiPixCount)
{

    if(Roi.empty())
        return Mat::zeros(0,0,CV_16U);
    if(ImIn.empty())
        return Mat::zeros(0,0,CV_16U);

    //unsigned short *wImIn = (unsigned short*)ImIn.data;
    //float *wImGradient = (float*)ImGradient.data;

    int maxX = ImIn.cols;
    int maxY = ImIn.rows;
    //int maxXY = maxX * maxY;
    if(Roi.cols != maxX)
        return Mat::zeros(0,0,CV_16U);
    if(Roi.rows != maxY)
        return Mat::zeros(0,0,CV_16U);


    int diameter = radius * 2 + 1;
    Mat RoiSmall = CreateRoi16(2, diameter, diameter);

    unsigned short *wRoiSmall = (unsigned short*)RoiSmall.data;
    int roiPixCount = 0;
    for(int y = 0; y < RoiSmall.rows; y++)
    {
        for(int x = 0; x < RoiSmall.cols; x++)
        {
            if(*wRoiSmall)
                roiPixCount++;
            wRoiSmall++;
        }
    }
    *outSDARoiPixCount = roiPixCount;
    Mat ImSDA = Mat::zeros(maxY, maxX, CV_16U);

    unsigned short *wImSDA = (unsigned short*)ImSDA.data;
    unsigned short *wImIn = (unsigned short*)ImIn.data;
    unsigned short *wRoi = (unsigned short*)Roi.data;

    int xLimMin = radius +1;
    int xLimMax = maxX - radius;
    int yLimMin = radius + 1;
    int yLimMax = maxY - radius;
    int maxXYSmall = diameter *diameter;

    for(int y = 0; y < maxY; y++)
    {
        for(int x = 0; x < maxX; x++)
        {
            if (*wRoi)
            {
                if(x > xLimMin && x < xLimMax && y > yLimMin && y < yLimMax )
                {
                    Mat ImSmall;
                    unsigned short pixVal = *wImIn;
                    int sum = 0;
                    ImIn(Rect(x - radius, y - radius, diameter,diameter)).copyTo(ImSmall);
                    unsigned short *wImSmall = (unsigned short*)ImSmall.data;
                    unsigned short *wRoiSmall = (unsigned short*)RoiSmall.data;
                    for(int i = 0; i < maxXYSmall; i++)
                    {
                        if(*wImSmall >= pixVal && *wRoiSmall)
                        {
                           sum++;
                        }
                        wImSmall++;
                        wRoiSmall++;
                    }
                    *wImSDA = sum;
                }
            }
            else
                *wImSDA = 0;
            wRoi++;
            wImIn++;
            wImSDA++;
        }
    }
    *outSDARoiPixCount = roiPixCount;
    return ImSDA;

}

//--------------------------------------------------------------------------------------------------

