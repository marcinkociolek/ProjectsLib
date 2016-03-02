#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "math.h"
#include <iostream>
#include "RedundantWaveletLib.h"

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
Mat RedundantWaveletLLFilter(int scale)
{
	int filterSize = (int)pow(2, scale);
    //int halfFilterSize = filterSize / 2;
	float filterMaxXY = (float)(filterSize*filterSize);
	float filterCoef = (float)(1.0) / filterMaxXY;

	Mat FilterLL = Mat::zeros(filterSize, filterSize, CV_32F);
	float *wFilterLL = (float*)FilterLL.data;

	for (int y = 0; y <filterSize; y++)
	{
		for (int x = 0; x <filterSize; x++)
		{
			*wFilterLL = filterCoef;
			wFilterLL++;
		}
	}
	return FilterLL;
}
//-----------------------------------------------------------------------------------------------------------------
Mat RedundantWaveletHLFilter(int scale)
{
	int filterSize = (int)pow(2, scale);
	int halfFilterSize = filterSize / 2;
	float filterMaxXY = (float)(filterSize*filterSize);
	float filterCoef = (float)(1.0) / filterMaxXY;
	float filterCoefN = filterCoef * (float)(-1.0);
	Mat FilterHL = Mat::zeros(filterSize, filterSize, CV_32F);
	float *wFilterHL = (float*)FilterHL.data;

	for (int y = 0; y <filterSize; y++)
	{
		for (int x = 0; x <filterSize; x++)
		{
			if (x < halfFilterSize)
				*wFilterHL = filterCoef;
			else
				*wFilterHL = filterCoefN;
			wFilterHL++;
		}
	}
	return FilterHL;
}
//-----------------------------------------------------------------------------------------------------------------
Mat RedundantWaveletLHFilter(int scale)
{
	int filterSize = (int)pow(2, scale);
	int halfFilterSize = filterSize / 2;
	float filterMaxXY = (float)(filterSize*filterSize);
	float filterCoef = (float)(1.0) / filterMaxXY;
	float filterCoefN = filterCoef * (float)(-1.0);

	Mat FilterLH = Mat::zeros(filterSize, filterSize, CV_32F);
	float *wFilterLH = (float*)FilterLH.data;

	for (int y = 0; y <filterSize; y++)
	{
		for (int x = 0; x <filterSize; x++)
		{
			if (y < halfFilterSize)
				*wFilterLH = filterCoef;
			else
				*wFilterLH = filterCoefN;
			wFilterLH++;
		}
	}
	return FilterLH;
}
//-----------------------------------------------------------------------------------------------------------------
Mat RedundantWaveletHHFilter(int scale)
{
	int filterSize = (int)pow(2, scale);
	int halfFilterSize = filterSize / 2;
	float filterMaxXY = (float)(filterSize*filterSize);
	float filterCoef = (float)(1.0)/ filterMaxXY;
	float filterCoefN = filterCoef * (float)(-1.0);

	Mat FilterHH = Mat::zeros(filterSize, filterSize, CV_32F);
	float *wFilterHH = (float*)FilterHH.data;

	for (int y = 0; y < filterSize; y++)
	{
		for (int x = 0; x < filterSize; x++)
		{
			if ((y < halfFilterSize && x < halfFilterSize) || (y >= halfFilterSize && x >= halfFilterSize))
				*wFilterHH = filterCoef;
			else
				*wFilterHH = filterCoefN;
			wFilterHH++;
		}
	}
	return FilterHH;
}
//-----------------------------------------------------------------------------------------------------------------
unsigned short RoiPositions(Mat Roi, int *minPosX, int *maxPosX, int *minPosY, int *maxPosY)
{

    int maxX, maxY;// maxXm1, maxYm1;
    maxX = Roi.cols;
    maxY = Roi.rows;

    for(int i = 0; i < 65536; i++)
    {
        minPosX[i] = maxX;
        maxPosX[i] = 0;
        minPosY[i] = maxY;
        maxPosY[i] = 0;

    }

    unsigned short maxRoi = 0;

    unsigned short *wRoi = (unsigned short*)Roi.data;
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            if (*wRoi > 0)
            {
                if(maxRoi < *wRoi)
                    maxRoi = *wRoi;

                if(minPosX[*wRoi] > x)
                    minPosX[*wRoi] = x;
                if(maxPosX[*wRoi] < x)
                    maxPosX[*wRoi] = x;

                if(minPosY[*wRoi] > y)
                    minPosY[*wRoi] = y;
                if(maxPosY[*wRoi] < y)
                    maxPosY[*wRoi] = y;
            }
            wRoi++;
        }
    }
    return maxRoi;
}


//-----------------------------------------------------------------------------------------------------------------
float MeanEnergyCalculaton(Mat ImIn,Mat Roi,unsigned short roiNr)
{
    int maxX, maxY;// maxXm1, maxYm1;
    maxX = ImIn.cols;
    maxY = ImIn.rows;

    int maxXRoi, maxYRoi;// maxXm1, maxYm1;
    maxXRoi = Roi.cols;
    maxYRoi = Roi.rows;

    if ((maxX != maxXRoi) | (maxY != maxYRoi))
        return -1;
    //	maxXm1 = maxX - 1;
    //	maxYm1 = maxY - 1;

    float *wImIn = (float*)ImIn.data;
    int pointsCount = 0;
    unsigned short *wRoi = (unsigned short*)Roi.data;
    double energy = 0;
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            if (*wRoi == roiNr)
            {
                energy += (double)(*wImIn) * (double)(*wImIn);
                pointsCount++;
            }

            wImIn++;
            wRoi++;
        }
    }
    return (float)(energy / double(pointsCount));
}
// ----------------------------------------------------------------------------------------------------------
Mat MeanEnergyImage(Mat ImIn, Mat Roi, unsigned short roiNr)
{
    int maxX, maxY;// maxXm1, maxYm1;
    maxX = ImIn.cols;
    maxY = ImIn.rows;

    int maxXRoi, maxYRoi;// maxXm1, maxYm1;
    maxXRoi = Roi.cols;
    maxYRoi = Roi.rows;

    Mat EnIm = Mat::zeros(maxY, maxX, CV_32F);

    if ((maxX != maxXRoi) | (maxY != maxYRoi))
        return EnIm;
    //	maxXm1 = maxX - 1;
    //	maxYm1 = maxY - 1;

    float *wEnIm = (float*)EnIm.data;
    float *wImIn = (float*)ImIn.data;
    unsigned short *wRoi = (unsigned short*)Roi.data;
    //double energy = 0;
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            if (*wRoi == roiNr)
                *wEnIm = (*wImIn * *wImIn);
            wEnIm++;
            wImIn++;
            wRoi++;
        }
    }
    return EnIm;
}
