#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <math.h>
#include <iostream>
#include "Functions.h"

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
int PrintMatFeatures(Mat Im)
{
	cout << "Mat params: cols- " << Im.cols << ", rows - " << Im.rows
		<< ", depch - ";
	switch (Im.depth())
	{
	case CV_8U:
		cout << "CV_8U";
		break;
	case CV_8S:
		cout << "CV_8S";
		break;
	case CV_16U:
		cout << "CV_16U";
		break;
	case CV_16S:
		cout << "CV_16S";
		break;
	case CV_32S:
		cout << "CV_32S";
		break;
	case CV_32F:
		cout << "CV_32F";
		break;
	case CV_64F:
		cout << "CV_64F";
		break;

	default:
		cout << "unknow";
		break;
	}
	cout << ", chanels - " << Im.channels();
	
	if (!Im.isContinuous())
	{
		cout << ", not continous";
	}
	else
	{
		cout << ", continous";
	}

	cout << endl;
	return 0;

}
//-----------------------------------------------------------------------------------------------------------------
int ShowImageInColorMap(Mat Im, int style, double minIm, double maxIm, const string &WinName)
{ 
	// 0 default as is
	// 1 min max
	//double	minIm, maxIm;
	double offset, scale;
	switch (style)
	{
    case 1:  //min max style
        minMaxIdx(Im, &minIm, &maxIm);
		break;
	case 2:
		break;
	default:
		minIm = 0;
		maxIm = 255;
		break;
	}

	scale = 255.0 / (maxIm - minIm);
	offset = scale * minIm;
	

	cout << "min " << std::to_string(minIm) << "; max " << std::to_string(maxIm)
		<< "; scale " << std::to_string(scale) << "; offset " << std::to_string(offset)
		 << endl;

	Mat ImTemp, ImShow;
	Im.convertTo(ImTemp, CV_64F);
	
	ImTemp = ImTemp * scale - offset;
	ImTemp.convertTo(ImTemp, CV_8U);

	ShowColorScale(minIm, maxIm, 128);

	applyColorMap(ImTemp, ImShow, COLORMAP_JET);
	namedWindow(WinName, WINDOW_AUTOSIZE);
	imshow(WinName, ImShow); 
	waitKey(0);

	return 1; 
}
//-----------------------------------------------------------------------------------------------------------------
int ShowColorScale(double min, double max, int maxX)
{
	Mat ColorScale = Mat::zeros(256, maxX, CV_8U);
	unsigned char *wColorScale = ColorScale.data;
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (x < 16)
				*wColorScale = y;
			wColorScale++;
		}
	}
	Mat ImShow;
	applyColorMap(ColorScale, ImShow, COLORMAP_JET);
	string MinTxt = std::to_string(min);
	string MaxTxt = std::to_string(max);
	Point minPos, maxPos;
	minPos.x = 16;
	minPos.y = 16;
	maxPos.x = 16;
	maxPos.y = 250;

	putText(ImShow, MinTxt, minPos, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255));
	putText(ImShow, MaxTxt, maxPos, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255));
	imshow("ColorScale", ImShow);
	return 0;
}
//-----------------------------------------------------------------------------------------------------------------
Mat ImageInPseudocolors(Mat Im, int style, double par1, double par2, double *minOut, double *maxOut)
{
	// 0 default as is
	// 1 min max
	double	minIm, maxIm;
	double offset, scale;
	switch (style)
	{
	case 1:  //min max style
		minMaxIdx(Im, &minIm, &maxIm);
		break;
	case 2:
		minIm = par1;
		maxIm = par2;
		break;
	case 3:  //min max style
        minMaxIdx(Im, &minIm, &maxIm);
		maxIm = maxIm / par1;
		break;
	default:
		minIm = 0;
		maxIm = 255;
		break;
	}
	if (minOut)
		*minOut = minIm;
	if (maxOut)
		*maxOut = maxIm;

	scale = 255.0 / (maxIm - minIm);
	offset = scale * minIm;

// to delete
//	cout << "min " << std::to_string(minIm) << "; max " << std::to_string(maxIm)
//		<< "; scale " << std::to_string(scale) << "; offset " << std::to_string(offset)
//		<< endl;
//
	Mat ImTemp, ImShow;
	Im.convertTo(ImTemp, CV_64F);

	ImTemp = ImTemp * scale - offset;
	ImTemp.convertTo(ImTemp, CV_8U);
	applyColorMap(ImTemp, ImShow, COLORMAP_JET);
	
	return ImShow;
}
//-----------------------------------------------------------------------------------------------------------------
Mat PrepareColorScale(double min, double max, int maxX)
{
	Mat ColorScale = Mat::zeros(256, maxX, CV_8U);
	unsigned char *wColorScale = ColorScale.data;
	for (int y = 255; y >= 0; y--)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (x < 16)
				*wColorScale = y;
			wColorScale++;
		}
	}
	Mat ImShow;
	applyColorMap(ColorScale, ImShow, COLORMAP_JET);
	string MinTxt = std::to_string((int)min);
	string MaxTxt = std::to_string((int)max);
	Point minPos, maxPos;
	minPos.x = 16;
	minPos.y = 250;
	maxPos.x = 16;
	maxPos.y = 20;

	putText(ImShow, MinTxt, minPos, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255));
	putText(ImShow, MaxTxt, maxPos, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255));
	
	return ImShow;
}
//-----------------------------------------------------------------------------------------------------------------
Mat KeepSize(Mat ImIn, int maxX, int maxY)
{
	Mat ImOut;
	int depth = ImIn.type();
	ImOut = Mat::zeros(maxX, maxY, depth);
	int scale = maxX / (ImIn.rows);
/*
	switch (depth)
	{
	case CV_8U:
		unsigned char *wImIn = ImIn.data;
		unsigned char *wImOut = ImOut.data;
		break;
	case CV_8S:
		signed char *wImIn = (signed char*)ImIn.data;
		signed char *wImOut = (signed char*)ImOut.data;
		break;
	case CV_16U:
		unsigned short *wImIn = (unsigned short*)ImIn.data;
		unsigned short *wImOut = (unsigned short*)ImOut.data;
		break;
	case CV_16S:
		signed short *wImIn = (signed short*)ImIn.data;
		signed short *wImOut = (signed short*)ImOut.data;
		break;
	case CV_32S:
		signed int *wImIn = (signed int*)ImIn.data;
		signed int *wImOut = (signed int*)ImOut.data;
		break;
	case CV_32F:
		float *wImIn = (float*)ImIn.data;
		float *wImOut = (float*)ImOut.data;
		break;
	case CV_64F:
		double *wImIn = (double*)ImIn.data;
		double *wImOut = (double*)ImOut.data;
		break;

	default:
		unsigned char *wImIn = ImIn.data;
		unsigned char *wImOut = ImOut.data;
		break;
	}
*/
	float *wImIn = (float*)ImIn.data;
	float *wImOut = (float*)ImOut.data;
	for (int y = 0; y < maxY; y++)
	{
		
		for (int x = 0; x < maxX; x++)
		{
			wImIn = (float*)ImIn.data + (y / scale * ImIn.cols) + x / scale;
			*wImOut = *wImIn;
			wImOut++;
			
		}
	}
	return ImOut;

}
//-----------------------------------------------------------------------------------------------------------------
Mat MultilevelContours(Mat RegIn)
{
	Mat RegOut;
	if (RegIn.depth() != CV_16U)
		return RegOut;
	
	
	int maxY, maxX, maxXB, maxYB;
	maxX = RegIn.cols;
	maxY = RegIn.rows;
	maxXB = maxX - 1;
	maxYB = maxY - 1;
	RegOut = Mat::zeros(maxY, maxX, CV_16U);

	unsigned short *wRegIn0, *wRegIn1, *wRegIn2, *wRegIn3, *wRegIn4, *wRegOut;

	wRegIn0 = (unsigned short *)RegIn.data;
	wRegOut = (unsigned short *)RegOut.data;
	wRegIn1 = wRegIn0 - maxX;
	wRegIn2 = wRegIn0 - 1;
	wRegIn3 = wRegIn0 + 1;
	wRegIn4 = wRegIn0 + maxX;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			int sum = 0;
			if (*wRegIn0)
			{
				if (y > 0)
					if(*wRegIn1 != *wRegIn0)
						sum++;
				if (x > 0 )
					if(*wRegIn2 != *wRegIn0)
						sum++;
				if (x < maxXB)
					if(*wRegIn3 != *wRegIn0)
						sum++;
				if (y < maxYB)
					if(*wRegIn4 != *wRegIn0)
						sum++;
			}
			if (sum)
				*wRegOut = *wRegIn0;
			wRegOut++;
			wRegIn0++;
			wRegIn1++;
			wRegIn2++;
			wRegIn3++;
			wRegIn4++;
		}
	}

	return RegOut;

}
//-----------------------------------------------------------------------------------------------------------------
int MarkContourOnPc(Mat ImIn, Mat RegIn)
{
	int maxY, maxX; // maxXB, maxYB;
	maxX = ImIn.cols;
	maxY = ImIn.rows;
	if ((maxX != RegIn.cols) | (maxY != RegIn.rows))
		return 0;
	if ((ImIn.depth() != CV_8U) | (ImIn.channels() != 3))
		return 0;
	if ((RegIn.depth() != CV_16U) | (RegIn.channels() != 1))
		return 0;

	unsigned short *wRegIn;
	unsigned char *wImInB, *wImInR, *wImInG;

	wRegIn = (unsigned short *)RegIn.data;
	wImInB = (unsigned char *)ImIn.data;
	wImInR = wImInB + 1;
	wImInG = wImInB + 2;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRegIn)
			{
				*wImInB = 255;
				*wImInR = 255;
				*wImInG = 255;
			}
			wRegIn++;
			wImInB+=3;
			wImInR += 3;
			wImInG += 3;
		}
	}
	return 1;
}

//-----------------------------------------------------------------------------------------------------------------
int MarkRegionOnPc(Mat ImIn, Mat RegIn, unsigned char B, unsigned char G, unsigned char R)
{
	int maxY, maxX; //maxXB, maxYB;
	maxX = ImIn.cols;
	maxY = ImIn.rows;
	if ((maxX != RegIn.cols) | (maxY != RegIn.rows))
		return 0;
	if ((ImIn.depth() != CV_8U) | (ImIn.channels() != 3))
		return 0;
	if ((RegIn.depth() != CV_16U) | (RegIn.channels() != 1))
		return 0;

	unsigned short *wRegIn;
	unsigned char *wImInB, *wImInR, *wImInG;

	wRegIn = (unsigned short *)RegIn.data;
	wImInB = (unsigned char *)ImIn.data;
	wImInR = wImInB + 1;
	wImInG = wImInB + 2;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRegIn)
			{
				*wImInB = B;
				*wImInR = G;
				*wImInG = R;
			}
			wRegIn++;
			wImInB += 3;
			wImInR += 3;
			wImInG += 3;
		}
	}
	return 1;
}
//---------------------------------------------------------------------------------------------
int MarkCircleleRegionOnPc(Mat ImIn, Mat RegIn)
{
	int maxY, maxX;// maxXB, maxYB;
	maxX = ImIn.cols;
	maxY = ImIn.rows;
	if ((maxX != RegIn.cols) | (maxY != RegIn.rows))
		return 0;
	if ((ImIn.depth() != CV_8U) | (ImIn.channels() != 3))
		return 0;
	if ((RegIn.depth() != CV_16U) | (RegIn.channels() != 1))
		return 0;

	unsigned short *wRegIn;
	//unsigned char *wImInR;

	wRegIn = (unsigned short *)RegIn.data;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRegIn)
			{
				circle(ImIn, Point(x, y), 6, Scalar(255, 255, 255), 2);

				Scalar color;
				switch (*wRegIn)
				{
				case 1:
					color = Scalar(0, 0, 255);
					break;
				case 2:
					color = Scalar(0, 150, 0);
					break;
				case 3:
					color = Scalar(255, 0, 0);
					break;
				case 4:
					color = Scalar(0, 100, 100);
					break;
				case 5:
					color = Scalar(100, 0, 100);
					break;
				default:
					color = Scalar(255,255,0);
					break;
				}
				circle(ImIn, Point(x, y), 5, color, -1);
			}
			wRegIn++;
		}
	}
	return 1;
}

//---------------------------------------------------------------------------------------------
Mat ColorRegionOnPc(Mat RegIn)
{
	int maxY, maxX;// maxXB, maxYB;
	maxX = RegIn.cols;
	maxY = RegIn.rows;
	Mat OutIm;
	OutIm = Mat::zeros(maxY, maxX, CV_8UC3);

	if ((RegIn.depth() != CV_16U) | (RegIn.channels() != 1))
		return OutIm;

	unsigned short *wRegIn;
	unsigned char *wOutImB, *wOutImR, *wOutImG;

	wOutImB = OutIm.data;
	wOutImG = OutIm.data + 1;
	wOutImR = OutIm.data + 2;
	wRegIn = (unsigned short *)RegIn.data;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRegIn)
			{
				switch (*wRegIn)
				{
				case 1:
					*wOutImB = 0;
					*wOutImG = 0;
					*wOutImR = 255;
					break;
				case 2:
					*wOutImB = 0;
					*wOutImG = 255;
					*wOutImR = 0;
					break;
				case 3:
					*wOutImB = 255;
					*wOutImG = 0;
					*wOutImR = 0;
					break;
				case 4:
					*wOutImB = 255;
					*wOutImG = 255;
					*wOutImR = 0;
					break;
				case 5:
					*wOutImB = 255;
					*wOutImG = 0;
					*wOutImR = 255;
					break;
				default:
					break;
				}
			}
			wRegIn++;
			wOutImB += 3;
			wOutImG += 3;
			wOutImR += 3;
		}
	}
	return OutIm;
}
//---------------------------------------------------------------------------------------------------------------
Mat RegionFromColor(Mat ColIm)
{
	int maxY, maxX;// maxXB, maxYB;
	maxX = ColIm.cols;
	maxY = ColIm.rows;
	Mat OutIm;
	OutIm = Mat::zeros(maxY, maxX, CV_16U);

	if ((ColIm.depth() != CV_8U) | (ColIm.channels() != 3))
		return OutIm;

	unsigned short *wOutIm;
	unsigned char *wColImB, *wColImR, *wColImG;

	wColImB = ColIm.data;
	wColImG = ColIm.data + 1;
	wColImR = ColIm.data + 2;
	wOutIm = (unsigned short *)OutIm.data;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wColImB || *wColImG || *wColImR)
			{
				if (*wColImB == 0 && *wColImG == 0 && *wColImR == 255)
					*wOutIm = 1;
				if (*wColImB == 0 && *wColImG == 255 && *wColImR == 0)
					*wOutIm = 2;
				if (*wColImB == 255 && *wColImG == 0 && *wColImR == 0)
					*wOutIm = 3;
				if (*wColImB == 255 && *wColImG == 255 && *wColImR == 0)
					*wOutIm = 4;
				if (*wColImB == 255 && *wColImG == 0 && *wColImR == 255)
					*wOutIm = 5;
			}
			wOutIm++;
			wColImB += 3;
			wColImG += 3;
			wColImR += 3;
		}
	}
	return OutIm;
}

//-----------------------------------------------------------------------------------------------------------------
float MeanEnergyCalculaton(Mat ImIn)
{
	int maxX, maxY;// maxXm1, maxYm1;
	maxX = ImIn.cols;
	maxY = ImIn.rows;
	//	maxXm1 = maxX - 1;
	//	maxYm1 = maxY - 1;

	float *wImIn = (float*)ImIn.data;
	double energy = 0;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			energy += (double)(*wImIn * *wImIn);
			wImIn++;
		}
	}
	return (float)(energy / double(maxX*maxY));
}
//-----------------------------------------------------------------------------------------------------------------
float MeanEnergyCalculaton(Mat ImIn,Mat Roi)
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
			if (*wRoi == 1)
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
Mat MeanEnergyImage(Mat ImIn, Mat Roi)
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
	double energy = 0;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRoi == 1)
				*wEnIm = (*wImIn * *wImIn);
			wEnIm++;
			wImIn++;
			wRoi++;
		}
	}
	return EnIm;
}
//-----------------------------------------------------------------------------------------------------------------
int MaskImageInPseudocolorsI(Mat ImIn, Mat Roi, unsigned char grayLevel)
{
	int maxX, maxY;
	maxX = ImIn.cols;
	maxY = ImIn.rows;

	int maxXRoi, maxYRoi;// maxXm1, maxYm1;
	maxXRoi = Roi.cols;
	maxYRoi = Roi.rows;

	Mat ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

	if ((maxX != maxXRoi) | (maxY != maxYRoi))
		return 0;
	//	maxXm1 = maxX - 1;
	//	maxYm1 = maxY - 1;

	unsigned char *wBImIn = (unsigned char*)ImIn.data; 
	unsigned char *wGImIn = wBImIn + 1;
	unsigned char *wRImIn = wBImIn + 2;
	unsigned short *wRoi = (unsigned short*)Roi.data;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRoi == 0)
			{
				*wBImIn = grayLevel;
				*wGImIn = grayLevel;
				*wRImIn = grayLevel;

			}
			
			wBImIn += 3;
			wGImIn += 3;
			wRImIn += 3;
			wRoi++;
		}
	}
	return 1;
}

//-----------------------------------------------------------------------------------------------------------------
float MeanAbsCalculaton(Mat ImIn, Mat Roi)
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
	double absVal = 0;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRoi == 1)
			{
				absVal += (double)(abs(*wImIn));
				pointsCount++;
			}

			wImIn++;
			wRoi++;
		}
	}
	return (float)(absVal / double(pointsCount));
}
// ----------------------------------------------------------------------------------------------------------
Mat AbsImage(Mat ImIn, Mat Roi)
{
	int maxX, maxY;// maxXm1, maxYm1;
	maxX = ImIn.cols;
	maxY = ImIn.rows;

	int maxXRoi, maxYRoi;// maxXm1, maxYm1;
	maxXRoi = Roi.cols;
	maxYRoi = Roi.rows;

	Mat AbsIm = Mat::zeros(maxY, maxX, CV_32F);

	if ((maxX != maxXRoi) | (maxY != maxYRoi))
		return AbsIm;
	//	maxXm1 = maxX - 1;
	//	maxYm1 = maxY - 1;

	float *wAbsIm = (float*)AbsIm.data;
	float *wImIn = (float*)ImIn.data;
	unsigned short *wRoi = (unsigned short*)Roi.data;
	double energy = 0;
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (*wRoi == 1)
				*wAbsIm = abs(*wImIn);
			wAbsIm++;
			wImIn++;
			wRoi++;
		}
	}
	return AbsIm;
}
// ----------------------------------------------------------------------------------------------------------



int RedundantWaveletEnergyFileOutput(Mat ImIn, bool displayResult, bool saveResult)
{
	return 0;
}

// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------
float MatFMeanRoi(Mat ImIn, Mat Roi,unsigned short roiNr)
{
	int maxXY = ImIn.cols  * ImIn.rows;
	
	if (!maxXY)
		return -1.0;
	if (ImIn.cols != Roi.cols || ImIn.rows != Roi.rows)
		return -2.0;
	if (ImIn.depth() != CV_32F)
		return -3.0;
	if (Roi.depth() != CV_16U)
		Roi.convertTo(Roi, CV_16U);

	float *wImIn = (float*)ImIn.data;
	unsigned char *wRoi = (unsigned char *)Roi.data;

	double sum = 0;
	int count = 0;
	
	for (int i = 0; i < maxXY; i++)
	{
		if (*wRoi == roiNr)
		{
			sum += double(*wImIn);
			count++;
		}
		wImIn++;
		wRoi++;
	}
	return (float)(sum / (double)count);
}
// ----------------------------------------------------------------------------------------------------------
float MatFMeanAndStd(Mat ImIn, float *mean, float *stdDev)
{
	int maxTileXY = ImIn.cols  * ImIn.rows;
	double sum = 0;
	float *wImIn;
	wImIn = (float*)ImIn.data;
	for (int i = 0; i < maxTileXY; i++)
	{
		sum += *wImIn;
		wImIn++;
	}
	double meanD = sum / maxTileXY;
	double sumDifSq = 0;
	wImIn = (float*)ImIn.data;
	for (int i = 0; i < maxTileXY; i++)
	{
		sumDifSq += (*wImIn - meanD) * (*wImIn - meanD);
		wImIn++;
	}
	float stdD = sqrt(sumDifSq / maxTileXY);

	*mean = (float)meanD;
	*stdDev = (float)stdD;
	return 1;

}

// ----------------------------------------------------------------------------------------------------------
int* MatFMeanAndStd(Mat ImIn, float *mean, float *stdDev, int *min, int *max)
{
	int maxXY = ImIn.cols  * ImIn.rows;
	double sum = 0;
	float locMin = 65536;
	float locMax = 0;
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
		sum += *wImIn;
		int histPos = int(*wImIn);
		if (histPos < 0)
			histPos = 0;
		if (histPos > 65535)
			histPos = 65535;

		if (locMin > *wImIn)
			locMin = *wImIn;

		if (locMax < *wImIn)
			locMax = *wImIn;

		Hist[histPos]++;
		wImIn++;
	}
	double meanD = sum / maxXY;
	double sumDifSq = 0;
	wImIn = (float*)ImIn.data;
	for (int i = 0; i < maxXY; i++)
	{
		sumDifSq += (*wImIn - meanD) * (*wImIn - meanD);
		wImIn++;
	}
	float stdD = sqrt(sumDifSq / maxXY);

	*mean = (float)meanD;
	*stdDev = (float)stdD;
	*min = (int)locMin;
	*max = (int)locMax;
	return Hist;

}

// ----------------------------------------------------------------------------------------------------------
int* FistogramFeatures(int* Histogram, int binSize, int *perc1, int *perc99, int *perm1, int *perm999)
{
	int *BinedHist = new int[1024];
	int sum = 0;
	int localSum = 0;
	int localCounter = 0;
	int counter = 0;
	int *wBinedHist = BinedHist;
	int *wHistogram = Histogram;
	for(int i = 0; i < 65536; i++)
	{
		localSum += *wHistogram;
		sum += *wHistogram;
		localCounter++;
		if ((localCounter >= binSize) && (counter < 1024))
		{
			*wBinedHist = localSum;
			wBinedHist++;
			localCounter = 0;
			localSum = 0;
			counter++;
		}
		wHistogram++;
	}
	
	
	int perc1Local = 0;
	int perc99Local = 0;
	int perm1Local = 0;
	int perm999Local = 0;


	int perc1Lim = sum / 100;
	int perc99Lim = sum - perc1Lim;
	int perm1Lim = sum / 1000;
	int perm999Lim = sum - perm1Lim;

	sum = 0;
	wHistogram = Histogram;
	for (int i = 0; i < 65536; i++)
	{
		sum += *wHistogram;
		if (perc1Lim > sum)
		{
			perc1Local = i;
		}
		if (perm1Lim > sum)
		{
			perm1Local = i;
		}
		if (perc99Lim >= sum)
		{
			perc99Local = i;
		}
		if (perm999Lim >= sum)
		{
			perm999Local = i;
		}
		wHistogram++;
	}
	*perc1 = perc1Local;
	*perm1 = perm1Local;
	*perc99 = perc99Local;
	*perm999 = perm999Local;
	return BinedHist;

}
