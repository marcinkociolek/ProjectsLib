#include "opencv2\core\core.hpp"
#include <math.h>
#include "NormalizationLib.h"
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax(Mat Im, float *maxNorm, float *minNorm)
{
	Mat ImF;
	Im.convertTo(ImF, CV_32F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

	float max = (float)(-100000.0);
	float min = (float)(100000.0);

	float *wImF = (float *)(ImF.data);
	for (int i = 0; i < maxXY; i++)
	{
		if (max < *wImF)
			max = *wImF;
		if (min > *wImF)
			min = *wImF;
		wImF++;
	}
	*maxNorm = max;
	*minNorm = min;
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std(Mat Im, float *maxNorm, float *minNorm)
{
	Mat ImF;
	Im.convertTo(ImF, CV_32F);
	int maxX, maxY, maxXY;
	maxX = Im.cols;
	maxY = Im.rows;
	maxXY = maxX * maxY;

	//float max = (float)(-100000.0);
	//float min = (float)(100000.0);
	double sum = 0;
	int count = 0;
	float *wImF = (float *)(ImF.data);
	for (int i = 0; i < maxXY; i++)
	{
		sum += (double)*wImF;
		count++;
		wImF++;
	}
	float mean = (float)(sum / ((double)(count)));
	double deviationSum = 0;
	wImF = (float *)(ImF.data);
	for (int i = 0; i < maxXY; i++)
	{
		float diff = *wImF - mean;
		deviationSum += (double)(diff * diff);
		wImF++;
	}
	float stdDev = sqrt((deviationSum) / ((double)(count - 1)));

	*maxNorm = mean + 3 * stdDev;
	*minNorm = mean - 3 * stdDev;
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc(Mat ImIn, float *maxNorm, float *minNorm)
{
	int maxXY = ImIn.cols  * ImIn.rows;

	int *Hist = new int[65536];
	int *wHist = Hist;
	for (int i = 0; i < 65536; i++)
	{
		*wHist = 0;
		wHist++;
	}

	float *wImIn;
	wImIn = (float*)ImIn.data;
	for (int i = 0; i < maxXY; i++)
	{
		float histPos = *wImIn;
		if (histPos < 0)
			histPos = 0;
		if (histPos > 65535)
			histPos = 65535;

		Hist[(int)(histPos)]++;
		wImIn++;
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
	return;
}

//-------------------------------------------------------------------------------------------------------------
void NormParamsMinMax(Mat Im, Mat Roi , unsigned short roiNr, float *maxNorm, float *minNorm)
{
	Mat ImF;
	Im.convertTo(ImF, CV_32F);
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
	float max = (float)(-100000.0);
	float min = (float)(100000.0);

	float *wImF = (float *)(ImF.data);
	unsigned short *wRoi = (unsigned short *)Roi.data;

	for (int i = 0; i < maxXY; i++)
	{
		if (max < *wImF || *wRoi == roiNr)
			max = *wImF;
		if (min > *wImF || *wRoi == roiNr)
			min = *wImF;
		wImF++;
		wRoi++;
	}
	*maxNorm = max;
	*minNorm = min;
}
//-------------------------------------------------------------------------------------------------------------
void NormParamsMeanP3Std(Mat Im, Mat Roi, unsigned short roiNr, float *maxNorm, float *minNorm)
{
	Mat ImF;
	Im.convertTo(ImF, CV_32F);
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
	//float max = (float)(-100000.0);
	//float min = (float)(100000.0);
	double sum = 0;
	int count = 0;
	float *wImF = (float *)(ImF.data);
	unsigned short *wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
			sum += (double)*wImF;
			count++;
		}
		wImF++;
		wRoi++;
	}
	float mean = (float)(sum / ((double)(count)));
	double deviationSum = 0;
	wImF = (float *)(ImF.data);
	wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
			float diff = *wImF - mean;
			deviationSum += (double)(diff * diff);
		}
		wImF++;
		wRoi++;
	}
	float stdDev = sqrt((deviationSum) / ((double)(count - 1)));

	*maxNorm = mean + 3 * stdDev;
	*minNorm = mean - 3 * stdDev;
}

//-------------------------------------------------------------------------------------------------------------
void NormParams1to99perc(Mat ImIn, Mat Roi, unsigned short roiNr, float *maxNorm, float *minNorm)
{
	int maxXY = ImIn.cols  * ImIn.rows;

	if (Roi.cols != ImIn.cols || Roi.rows != ImIn.rows || Roi.depth() != CV_16U)
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
	float *wImIn;
	unsigned short *wRoi;
	wImIn = (float*)ImIn.data;
	wRoi = (unsigned short *)Roi.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
			float histPos = *wImIn;
			if (histPos < 0)
				histPos = 0;
			if (histPos > 65535)
				histPos = 65535;

			Hist[(int)(histPos)]++;
			count++;
		}
		wImIn++;
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
	return;
}