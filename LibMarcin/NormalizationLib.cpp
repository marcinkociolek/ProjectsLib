//#include "opencv2\core\core.hpp"
#include <math.h>
#include "NormalizationLib.h"

using namespace cv;
using namespace std;
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax(Mat Im, double *maxNorm, double *minNorm)
{
    Mat ImD;
    Im.convertTo(ImD, CV_64F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

    double max = -1.0E+308;
    double min = 1.0E+308;

    double *wImD = (double *)(ImD.data);
	for (int i = 0; i < maxXY; i++)
	{
        if (max < *wImD)
            max = *wImD;
        if (min > *wImD)
            min = *wImD;
        wImD++;
	}
	*maxNorm = max;
	*minNorm = min;
    ImD.release();
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std(Mat Im, double *maxNorm, double *minNorm)
{
    Mat ImD;
    Im.convertTo(ImD, CV_64F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

    double sum = 0.0;
	int count = 0;
    double *wImD = (double *)(ImD.data);
	for (int i = 0; i < maxXY; i++)
	{
        sum += *wImD;
		count++;
        wImD++;
	}
    double mean = (sum / ((double)(count)));
    double deviationSum = 0.0;
    wImD = (double *)(ImD.data);
	for (int i = 0; i < maxXY; i++)
	{
        double diff = *wImD - mean;
        deviationSum += (diff * diff);
        wImD++;
	}
    double stdDev = sqrt((deviationSum) / ((double)(count - 1)));

	*maxNorm = mean + 3 * stdDev;
	*minNorm = mean - 3 * stdDev;
    ImD.release();
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc(Mat Im,  double *maxNorm, double *minNorm)
{
    int maxXY = Im.cols  * Im.rows;

	int *Hist = new int[65536];
	int *wHist = Hist;
	for (int i = 0; i < 65536; i++)
	{
		*wHist = 0;
		wHist++;
	}

    Mat ImD;
    Im.convertTo(ImD, CV_64F);

    double *wImD;
    wImD = (double*)ImD.data;
	for (int i = 0; i < maxXY; i++)
	{
        double histPos = *wImD;
        if (histPos < 0.0)
            histPos = 0.0;
        if (histPos > 65535.0)
            histPos = 65535.0;

		Hist[(int)(histPos)]++;
        wImD++;
	}

	int perc1Local = 0;
	int perc99Local = 0;

	int perc1Lim = maxXY / 100;
	int perc99Lim = maxXY - perc1Lim;

	int sum = 0;
	wHist = Hist;
	for (int i = 0; i < 65536; i++)
	{
		sum += Hist[i];
		if (perc1Lim > sum)
		{
			perc1Local = i;
		}
		if (perc99Lim >= sum)
		{
			perc99Local = i;
		}
		wHist++;
	}
	*minNorm = perc1Local;
	*maxNorm = perc99Local;
	delete[] Hist;
    ImD.release();
	return;
}

//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax(Mat Im, Mat Roi , unsigned short roiNr, double *maxNorm, double *minNorm)
{
    Mat ImD;
    Im.convertTo(ImD, CV_64F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

	if (Roi.cols != maxX || Roi.rows != maxY || Roi.depth() != CV_16U)
	{
		*maxNorm = -10000;
		*minNorm = -10001;
		return;
	}
    double max = -1.0E+308;
    double min =  1.0E+308;

    double *wImD = (double *)(ImD.data);
	unsigned short *wRoi = (unsigned short *)Roi.data;

	for (int i = 0; i < maxXY; i++)
	{
        double val = *wImD;
        if(!(val != val))
        {
            if (max < val && *wRoi == roiNr)
                max = val;
            if (min > val && *wRoi == roiNr)
                min = val;
        }
        wImD++;
        wRoi++;
	}
	*maxNorm = max;
	*minNorm = min;
    ImD.release();
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std(Mat Im, Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm)
{
    Mat ImD;
    Im.convertTo(ImD, CV_64F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

	if (Roi.cols != maxX || Roi.rows != maxY || Roi.depth() != CV_16U)
	{
		*maxNorm = -10000;
		*minNorm = -10001;
		return;
	}

	double sum = 0;
	int count = 0;
    double *wImD = (double *)(ImD.data);
	unsigned short *wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
            sum += (double)*wImD;
			count++;
		}
        wImD++;
		wRoi++;
	}
    double mean = (double)(sum / ((double)(count)));
	double deviationSum = 0;
    wImD = (double *)(ImD.data);
	wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
            double diff = *wImD - mean;
            deviationSum += (diff * diff);
		}
        wImD++;
		wRoi++;
	}
    double stdDev = sqrt((deviationSum) / ((double)(count - 1)));

	*maxNorm = mean + 3 * stdDev;
	*minNorm = mean - 3 * stdDev;
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc(Mat Im, Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm)
{
    Mat ImD;
    Im.convertTo(ImD, CV_64F);
    int maxXY = Im.cols  * Im.rows;

    if (Roi.cols != Im.cols || Roi.rows != Im.rows || Roi.depth() != CV_16U)
	{
		*maxNorm = -10000;
		*minNorm = -10001;
		return;
	}

	int *Hist = new int[65536];
	int *wHist = Hist;
	for (int i = 0; i < 65536; i++)
	{
		*wHist = 0;
		wHist++;
	}

	int count = 0;
    double *wImD;
	unsigned short *wRoi;
    wImD = (double*)ImD.data;
	wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
            double histPos = *wImD;
			if (histPos < 0)
				histPos = 0;
			if (histPos > 65535)
				histPos = 65535;

			Hist[(int)(histPos)]++;
			count++;
		}
        wImD++;
		wRoi++;
	}

	int perc1Local = 0;
	int perc99Local = 0;

	int perc1Lim = count / 100;
	int perc99Lim = count - perc1Lim;

	int sum = 0;
	wHist = Hist;
	for (int i = 0; i < 65536; i++)
	{
		sum += Hist[i];
		if (perc1Lim > sum)
		{
			perc1Local = i;
		}
		if (perc99Lim >= sum)
		{
			perc99Local = i;
		}
		wHist++;
	}
	*minNorm = perc1Local;
	*maxNorm = perc99Local;
    delete[] Hist;
    ImD.release();
	return;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax16U(Mat Im, double *maxNorm, double *minNorm)
{
    if(Im.depth() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }
    int maxX, maxY, maxXY;
    maxX = Im.cols;
    maxY = Im.rows;
    maxXY = maxX * maxY;

    uint16_t max = 0;
    uint16_t min = 65535;

    uint16_t *wIm = (uint16_t *)(Im.data);
    for (int i = 0; i < maxXY; i++)
    {
        if (max < *wIm)
            max = *wIm;
        if (min > *wIm)
            min = *wIm;
        wIm++;
    }
    *maxNorm = (double)max;
    *minNorm = (double)min;
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std16U(Mat Im, double *maxNorm, double *minNorm)
{
    if(Im.depth() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }
    int maxX, maxY, maxXY;
    maxX = Im.cols;
    maxY = Im.rows;
    maxXY = maxX * maxY;

    double sum = 0.0;
    int count = 0;
    uint16_t *wIm = (uint16_t *)(Im.data);
    for (int i = 0; i < maxXY; i++)
    {
        sum += (double)*wIm;
        count++;
        wIm++;
    }
    double mean = (sum / ((double)(count)));
    double deviationSum = 0.0;
    wIm = (uint16_t *)(Im.data);
    for (int i = 0; i < maxXY; i++)
    {
        double diff = *wIm - mean;
        deviationSum += (diff * diff);
        wIm++;
    }
    double stdDev = sqrt((deviationSum) / ((double)(count - 1)));

    *maxNorm = mean + 3.0 * stdDev;
    *minNorm = mean - 3.0 * stdDev;
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc16U(Mat Im,  double *maxNorm, double *minNorm)
{
    if(Im.depth() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }

    int maxXY = Im.cols  * Im.rows;

    int *Hist = new int[65536];
    int *wHist = Hist;
    for (int i = 0; i < 65536; i++)
    {
        *wHist = 0;
        wHist++;
    }

    uint16_t *wIm = (uint16_t *)Im.data;
    for (int i = 0; i < maxXY; i++)
    {
        Hist[*wIm]++;
        wIm++;
    }

    int perc1Local = 0;
    int perc99Local = 0;

    int perc1Lim = maxXY / 100;
    int perc99Lim = maxXY - perc1Lim;

    int sum = 0;
    wHist = Hist;
    for (int i = 0; i < 65536; i++)
    {
        sum += Hist[i];
        if (perc1Lim > sum)
        {
            perc1Local = i;
        }
        if (perc99Lim >= sum)
        {
            perc99Local = i;
        }
        wHist++;
    }
    *minNorm = (double)perc1Local;
    *maxNorm = (double)perc99Local;
    delete[] Hist;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax16U(Mat Im, Mat Roi , unsigned short roiNr, double *maxNorm, double *minNorm)
{
    if(Im.depth() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }
    int maxX, maxY, maxXY;
    maxX = Im.cols;
    maxY = Im.rows;
    maxXY = maxX * maxY;

    if (Roi.cols != maxX || Roi.rows != maxY || Roi.depth() != CV_16U)
    {
        *maxNorm = -10000;
        *minNorm = -10001;
        return;
    }
    double max = -100000.0;
    double min = 100000.0;

    uint16_t *wIm = (uint16_t *)(Im.data);
    uint16_t *wRoi = (uint16_t *)Roi.data;

    for (int i = 0; i < maxXY; i++)
    {
        if (max < *wIm || *wRoi == roiNr)
            max = *wIm;
        if (min > *wIm || *wRoi == roiNr)
            min = *wIm;
        wIm++;
        wRoi++;
    }
    *maxNorm = max;
    *minNorm = min;
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std16U(Mat Im, Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm)
{
    if(Im.depth() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }

    int maxX, maxY, maxXY;
    maxX = Im.cols;
    maxY = Im.rows;
    maxXY = maxX * maxY;

    if (Roi.cols != maxX || Roi.rows != maxY || Roi.depth() != CV_16U)
    {
        *maxNorm = -10000;
        *minNorm = -10001;
        return;
    }
    double sum = 0;
    int count = 0;
    uint16_t *wIm = (uint16_t *)(Im.data);
    uint16_t *wRoi = (uint16_t *)Roi.data;
    for (int i = 0; i < maxXY; i++)
    {
        if (*wRoi == roiNr)
        {
            sum += (double)*wIm;
            count++;
        }
        wIm++;
        wRoi++;
    }
    double mean = sum / ((double)(count));
    double deviationSum = 0;
    wIm = (uint16_t *)(Im.data);
    wRoi = (uint16_t *)Roi.data;
    for (int i = 0; i < maxXY; i++)
    {
        if (*wRoi == roiNr)
        {
            double diff = (double)*wIm - mean;
            deviationSum += (diff * diff);
        }
        wIm++;
        wRoi++;
    }
    double stdDev = sqrt((deviationSum) / ((double)(count - 1)));

    *maxNorm = mean + 3 * stdDev;
    *minNorm = mean - 3 * stdDev;
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc16U(Mat Im, Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm)
{
    if(Im.type() != CV_16U)
    {
        *maxNorm = -68000.0;
        *minNorm = -67000.0;
        return;
    }

    int maxXY = Im.cols  * Im.rows;

    if (Roi.cols != Im.cols || Roi.rows != Im.rows || Roi.depth() != CV_16U)
    {
        *maxNorm = -10000;
        *minNorm = -10001;
        return;
    }

    int *Hist = new int[65536];
    int *wHist = Hist;
    for (int i = 0; i < 65536; i++)
    {
        *wHist = 0;
        wHist++;
    }

    int count = 0;
    uint16_t *wIm = (uint16_t*)Im.data;
    uint16_t *wRoi = (uint16_t *)Roi.data;
    for (int i = 0; i < maxXY; i++)
    {
        if (*wRoi == roiNr)
        {
            Hist[*wIm]++;
            count++;
        }
        wIm++;
        wRoi++;
    }

    int perc1Local = 0;
    int perc99Local = 0;

    int perc1Lim = count / 100;
    int perc99Lim = count - perc1Lim;

    int sum = 0;
    wHist = Hist;
    for (int i = 0; i < 65536; i++)
    {
        sum += Hist[i];
        if (perc1Lim > sum)
        {
            perc1Local = i;
        }
        if (perc99Lim >= sum)
        {
            perc99Local = i;
        }
        wHist++;
    }
    *minNorm = (double)perc1Local;
    *maxNorm = (double)perc99Local;
    delete[] Hist;
    return;
}
