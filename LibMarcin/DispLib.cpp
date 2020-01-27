//---------------------------------------------------------------------------
//#include <math.h>
#include "DispLib.h"

//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <string>

using namespace cv;
using namespace std;
//---------------------------------------------------------------------------

//#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Mat ShowImage8PseudoColor(Mat Im8, double minVal, double maxVal)
{
    int maxX = Im8.cols;
    int maxY = Im8.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    double difference = maxVal - minVal;
    if(difference < 1)
        difference = 1;
    double gain = 255/difference;
    double offset = gain * minVal;

    double value;
    unsigned char index;

    unsigned char *wIm8 = (unsigned char *)Im8.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {

        value = (double)(*wIm8) * gain - offset;
        if (value > 255)
            value = 255;
        if (value < 0)
            value = 0;
        index = (char)floor(value);

        *wImOut = colormapB[index];
        wImOut++;
        *wImOut = colormapG[index];
        wImOut++;
        *wImOut = colormapR[index];
        wImOut++;
        wIm8++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowImage16PseudoColor(Mat Im16, double minVal, double maxVal)
{
    int maxX = Im16.cols;
    int maxY = Im16.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    double difference = maxVal - minVal;
    if(difference == 0.0)
        difference = 1.0;
    double gain = 255.0/difference;
    double offset = gain * minVal;

    double value;
    unsigned char index;

    unsigned short *wIm16 = (unsigned short *)Im16.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {
  
        value = (double)(*wIm16) * gain - offset;
        if (value > 255.0)
            value = 255.0;
        if (value < 0.0)
            value = 0.0;
        index = (char)floor(value);

		*wImOut = colormapB[index];
		wImOut++;
		*wImOut = colormapG[index];
		wImOut++;
		*wImOut = colormapR[index];
		wImOut++;
		wIm16++;
	}
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowImage16Gray(Mat Im16, double minVal, double maxVal)
{
    int maxX = Im16.cols;
    int maxY = Im16.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    double difference = maxVal - minVal;
    if(difference == 0.0)
        difference = 1.0;
    double gain = 255.00/difference;
    double offset = gain * minVal;

    double value;
    unsigned char index;

    unsigned short *wIm16 = (unsigned short *)Im16.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {

        value = (double)(*wIm16) * gain - offset;
        if (value > 255)
            value = 255;
        if (value < 0)
            value = 0;
        index = (char)floor(value);

        *wImOut = index;
        wImOut++;
        *wImOut = index;
        wImOut++;
        *wImOut = index;
        wImOut++;
        wIm16++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowImageF32PseudoColor(Mat ImF, double minVal, double maxVal)
{
    int maxX = ImF.cols;
    int maxY = ImF.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    double difference = maxVal - minVal;
    if(difference == 0.0)
        difference = 1.0;
    double gain = 255.0/difference;
    double offset = gain * minVal;

    double value;
    int index;

    float *wImF = (float *)ImF.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {
        value = (double)*wImF * gain - offset;
        if (value > 255.0)
            value = 255.0;
        if (value < 0.0)
            value = 0.0;
        index = (int)floor(value);

		*wImOut = colormapB[index];
		wImOut++;
		*wImOut = colormapG[index];
		wImOut++;
		*wImOut = colormapR[index];
		wImOut++;
		wImF++;
	}
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowImageF64PseudoColor(Mat ImF, double minVal, double maxVal)
{
    int maxX = ImF.cols;
    int maxY = ImF.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    double difference = maxVal - minVal;
    if(difference == 0.0)
        difference = 1.0;
    double gain = 255.0/difference;
    double offset = gain * minVal;

    double value;
    int index;

    double *wImF = (double *)ImF.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {
        value = *wImF * gain - offset;
        if (value > 255)
            value = 255;
        if (value < 0)
            value = 0;
        index = (int)floor(value);

        *wImOut = colormapB[index];
        wImOut++;
        *wImOut = colormapG[index];
        wImOut++;
        *wImOut = colormapR[index];
        wImOut++;
        wImF++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowRegion(Mat ImReg)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;

    if(!maxXY)
        return ImOut;

    ImOut = Mat::zeros(maxY, maxX, CV_8UC3);

    unsigned short *wImReg = (unsigned short *)ImReg.data;
    char *wImOut = (char *)ImOut.data;

    for (int i = 0; i < maxXY; i++)
    {
		int y = i / maxX;
		int x = i % maxX;


		if(*wImReg)
        {
            *wImOut = RegColorsB[(*wImReg-1)%16];
            wImOut++;
            *wImOut = RegColorsG[(*wImReg-1)%16];
            wImOut++;
            *wImOut = RegColorsR[(*wImReg-1)%16];
            wImOut++;
        }
        else
        {
            wImOut++;
            wImOut++;
            wImOut++;
        }
        wImReg++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowSolidRegionOnImage(Mat ImReg, Mat ImRGB)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;
    ImRGB.copyTo(ImOut);


    unsigned short * wImReg = (unsigned short *)ImReg.data;
    char *wImOut = (char *)ImOut.data;
    for (int i = 0; i < maxXY; i++)
    {
            if(*wImReg)
            {
                int index = (int(*wImReg)-1)%16;
                *wImOut = RegColorsB[index];
                wImOut++;
                *wImOut = RegColorsG[index];
                wImOut++;
                *wImOut = RegColorsR[index];
                wImOut++;
            }
            else
            {
                wImOut++;
                wImOut++;
                wImOut++;
            }

            wImReg++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
Mat ShowTransparentRegionOnImage(Mat ImReg, Mat ImRGB, int transparency)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;
    ImRGB.copyTo(ImOut);


    unsigned short * wImReg = (unsigned short *)ImReg.data;
    unsigned char *wImOut = (unsigned char *)ImOut.data;
    for (int i = 0; i < maxXY; i++)
    {
            if(*wImReg)
            {
                int index = (int(*wImReg)-1)%16;
                int temp;

                temp = (int)*wImOut + RegColorsB[index]*transparency/100;
                if(temp > 255)
                    temp = 255;
                *wImOut = (unsigned char)temp;
                wImOut++;

                temp = (int)*wImOut + RegColorsG[index]*transparency/100;
                if(temp > 255)
                    temp = 255;
                *wImOut = (unsigned char)temp;
                wImOut++;


                temp = (int)*wImOut + RegColorsR[index]*transparency/100;
                if(temp > 255)
                    temp = 255;
                *wImOut = (unsigned char)temp;
                wImOut++;

            }
            else
            {
                wImOut++;
                wImOut++;
                wImOut++;
            }

            wImReg++;
    }
    return ImOut;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Mat ShowSolidRegionOnImageInBlack(Mat ImReg, Mat ImRGB)
{
	int maxX = ImReg.cols;
	int maxY = ImReg.rows;
	int maxXY = maxX * maxY;

	Mat ImOut;
	ImRGB.copyTo(ImOut);


	unsigned short * wImReg = (unsigned short *)ImReg.data;
	char *wImOut = (char *)ImOut.data;
	for (int i = 0; i < maxXY; i++)
	{
		if (*wImReg)
		{
			*wImOut = 0;
			wImOut++;
			*wImOut = 0;
			wImOut++;
			*wImOut = 0;
			wImOut++;
		}
		else
		{
			wImOut++;
			wImOut++;
			wImOut++;
		}

		wImReg++;
	}
	return ImOut;
}
//---------------------------------------------------------------------------
cv::Mat ShowSolidRegionOnImageInGray(cv::Mat ImReg, cv::Mat ImRGB, unsigned char grayLevel)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    int maxXY = maxX * maxY;

    Mat ImOut;
    ImRGB.copyTo(ImOut);

    if(ImRGB.type() != CV_8UC3)
        return ImOut;

    unsigned short * wImReg = (unsigned short *)ImReg.data;
    char *wImOut = (char *)ImOut.data;
    for (int i = 0; i < maxXY; i++)
    {
        if (*wImReg)
        {
            *wImOut = grayLevel;
            wImOut++;
            *wImOut = grayLevel;
            wImOut++;
            *wImOut = grayLevel;
            wImOut++;
        }
        else
        {
            wImOut++;
            wImOut++;
            wImOut++;
        }

        wImReg++;
    }
    return ImOut;
}


//-----------------------------------------------------------------------------------------------------------------
int MaskImageInPseudocolors(Mat ImIn, Mat Roi, unsigned char grayLevel)
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
//---------------------------------------------------------------------------
void ShowImageCombination(bool show, string WinName, Mat Im1, Mat Im2)
{
    if(!show)
        return;
    int imMaxX, imMaxY;
    imMaxX = Im1.cols;
    if (imMaxX < Im2.cols)
        imMaxX = Im2.cols;
    imMaxY = Im1.rows;
    if (imMaxY < Im2.rows)
        imMaxY = Im2.rows;
    Mat Im = Mat::zeros(Size(imMaxX *2,imMaxY) ,Im1.type());
    Im1.copyTo(Im(Rect(0, 0, Im1.cols , Im1.rows)));
    Im2.copyTo(Im(Rect(imMaxX, 0, Im2.cols , Im2.rows)));
    imshow(WinName.c_str(), Im);
    Im.release();

}
//---------------------------------------------------------------------------
void DispImage8PC(bool show, string WinName, Mat Im1)
{
    if(!show)
        return;
    int imMaxX, imMaxY;
    imMaxX = Im1.cols;
    Mat Im;
    Im1.copyTo(Im);
    imshow(WinName.c_str(), Im);
    Im.release();

}
//--------------------------------------------------------------------------------------------------
void ShowImageRegionCombination(bool show, bool showContour, string WinName, Mat Im1, Mat Im2, Mat Mask1, Mat Mask2)
{
    if(!show)
        return;
    int imMaxX, imMaxY;
    imMaxX = Im1.cols;
    if (imMaxX < Im2.cols)
        imMaxX = Im2.cols;
    imMaxY = Im1.rows;
    if (imMaxY < Im2.rows)
        imMaxY = Im2.rows;
    Mat Im = Mat::zeros(Size(imMaxX *2,imMaxY) ,Im1.type());
    Im1.copyTo(Im(Rect(0, 0, Im1.cols , Im1.rows)));
    Im2.copyTo(Im(Rect(imMaxX, 0, Im2.cols , Im2.rows)));

    Mat Mask = Mat::zeros(Size(imMaxX *2,imMaxY) ,Mask1.type());
    Mask1.copyTo(Mask(Rect(0, 0, Im1.cols , Im1.rows)));
    Mask2.copyTo(Mask(Rect(imMaxX, 0, Im2.cols , Im2.rows)));

    if(showContour)
    {
        Mask = GetContour5(Mask);
    }
    imshow(WinName.c_str(), ShowSolidRegionOnImage(Mask,Im));
    Mask.release();
    Im.release();
}

//--------------------------------------------------------------------------------------------------
void ShowHLinesOnImage(bool show, string WinName, Mat Im1, Mat Im2, int lineU, int lineCU, int lineCL, int lineL)
{
    if(!show)
        return;
    int imMaxX = Im1.cols;
    if(imMaxX < Im2.cols)
        imMaxX = Im2.cols;
    int imMaxY = Im1.rows;
    if(imMaxY < Im2.rows)
        imMaxY = Im2.rows;

    Mat ImShow = Mat::zeros(Size(imMaxX *2,imMaxY) ,Im1.type());
    Im1.copyTo(ImShow(Rect(0, 0, Im1.cols, Im1.rows)));
    Im2.copyTo(ImShow(Rect(imMaxX, 0, Im2.cols, Im2.rows)));

    //Mat ImShow;
    //Im.copyTo(ImShow);
    line(ImShow,Point(0,lineU),Point(ImShow.cols,lineU),CV_RGB(255,0,0),1);
    line(ImShow,Point(0,lineCU),Point(ImShow.cols,lineCU),CV_RGB(255,0,0),1);
    line(ImShow,Point(0,lineCL),Point(ImShow.cols,lineCL),CV_RGB(0,255,0),1);
    line(ImShow,Point(0,lineL),Point(ImShow.cols,lineL),CV_RGB(0,255,0),1);


    imshow(WinName.c_str(), ImShow);
    ImShow.release();
}
//------------------------------------------------------------------------------
void ShowRegBetweenHLinesOnImage(bool show, string WinName, Mat Im1, Mat Im2, Mat Mask1, Mat Mask2, int lines)
{
    if(!show)
        return;
    int imMaxX = Im1.cols;
    if(imMaxX < Im2.cols)
        imMaxX = Im2.cols;
    int imMaxY = Im1.rows;
    if(imMaxY < Im2.rows)
        imMaxY = Im2.rows;

    Mat ImShow = Mat::zeros(Size(imMaxX *2,imMaxY) ,Im1.type());
    Im1.copyTo(ImShow(Rect(0, 0, Im1.cols, Im1.rows)));
    Im2.copyTo(ImShow(Rect(imMaxX, 0, Im2.cols, Im2.rows)));

    Mat Mask1Temp;
    Mask1.copyTo(Mask1Temp);
    unsigned short * wMask = (unsigned short *)Mask1Temp.data;
    for (int y = 0; y < Mask1Temp.rows; y++)
        for (int x = 0; x < Mask1Temp.cols; x++)
        {
            if (*wMask)
            {
                if(y < lines)
                {
                    *wMask = 1;
                }
                else if (y >= (Mask1Temp.rows - lines))
                {
                    *wMask = 2;
                }
                else
                    *wMask = 0;
            }
            wMask++;
        }

    Mat Mask2Temp;
    Mask2.copyTo(Mask2Temp);
    wMask = (unsigned short *)Mask2Temp.data;
    for (int y = 0; y < Mask2Temp.rows; y++)
        for (int x = 0; x < Mask2Temp.cols; x++)
        {
            if (*wMask)
            {
                if(y < lines)
                {
                    *wMask = 1;
                }
                else if (y >= (Mask2Temp.rows - lines))
                {
                    *wMask = 2;
                }
                else
                    *wMask = 0;
            }

            wMask++;
        }



    //Mat ImShow;
    //Im.copyTo(ImShow);
//    line(ImShow,Point(0,lineU),Point(ImShow.cols,lineU),CV_RGB(255,0,0),1);
//    line(ImShow,Point(0,lineCU),Point(ImShow.cols,lineCU),CV_RGB(255,0,0),1);
//    line(ImShow,Point(0,lineCL),Point(ImShow.cols,lineCL),CV_RGB(0,255,0),1);
//    line(ImShow,Point(0,lineL),Point(ImShow.cols,lineL),CV_RGB(0,255,0),1);

    Mat Mask = Mat::zeros(Size(imMaxX *2,imMaxY) ,Mask1.type());
    Mask1Temp.copyTo(Mask(Rect(0, 0, Im1.cols , Im1.rows)));
    Mask2Temp.copyTo(Mask(Rect(imMaxX, 0, Im2.cols , Im2.rows)));

    bool showContour = false;
    if(showContour)
    {
        Mask = GetContour5(Mask);
    }
    imshow(WinName.c_str(), ShowRegion(Mask));
    Mask1Temp.release();
    Mask2Temp.release();
    Mask.release();
    ImShow.release();
}
//--------------------------------------------------------------------------------------------------
Mat GetContour5(Mat ImR)
{
    //modyfied version works on whole image
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;

    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    Mat ImOut = Mat::zeros(maxY,maxX, CV_16U);

    unsigned short *wImOut = (unsigned short*)ImOut.data;



    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX;
    unsigned short *wImR2 = wImR0 - 1;
    unsigned short *wImR3 = wImR0 + 1;
    unsigned short *wImR4 = wImR0 + maxX;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = 1;
        if (y > 0 && *wImR0 != *wImR1)
        {
            product *= 0;
        }
        if (x > 0 && *wImR0 != *wImR2)
        {
            product *= 0;
        }
        if (x < maxXa && *wImR0 != *wImR3)
        {
            product *= 0;
        }
        if (y < maxYa && *wImR0 != *wImR4)
        {
            product *= 0;
        }
        if(!product && *wImR0)
            *wImOut = *wImR0;
        else
            *wImOut = 0;

        wImOut++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
    }
    return ImOut;
}
//------------------------------------------------------------------------------
void GetContour9(Mat ImR)
{
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;

    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX - 1;
    unsigned short *wImR2 = wImR0 - maxX;
    unsigned short *wImR3 = wImR0 - maxX + 1;
    unsigned short *wImR4 = wImR0 - 1;
    unsigned short *wImR5 = wImR0 + 1;
    unsigned short *wImR6 = wImR0 + maxX - 1;
    unsigned short *wImR7 = wImR0 + maxX;
    unsigned short *wImR8 = wImR0 + maxX + 1;


    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;
        if (x > 0 && x < maxXa && y > 0 && y < maxYa)
        {
            if(*wImR0 && !(*wImR1 *  *wImR2 * *wImR3  * *wImR4
                      * *wImR5 *  *wImR6 * *wImR7  * *wImR8))
                *wImRTemp = *wImR0;
            else
                *wImRTemp = 0;
        }
        else
            *wImRTemp = 0;

        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}

/*
//---------------------------------------------------------------------------
void ShowRegionOnImage16(Mat ImReg, unsigned short *Im16,
                         Graphics::TBitmap *Bitmap, int maxX,int maxY,
                         int minVal, int maxVal)
{
    if(Bitmap->Height != maxY)
        Bitmap->Height = maxY;
    if(Bitmap->Width != maxX)
        Bitmap->Width = maxX;
    if(Bitmap->PixelFormat != pf32bit)
        Bitmap->PixelFormat = pf32bit;

    float difference = maxVal - minVal;
    if(difference == 0)
        difference = 1;
    float CoefA = 255/difference;
    float CoefB = CoefA * minVal;

    unsigned short *wImReg = ImReg;
    unsigned short *wIm16 = Im16;

    RGBQUAD *wBitmap;

    for (int y = 0; y < maxY; y++)
    {
        wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
        for (int x = 0; x < maxX; x++)
        {
            float value = *wIm16 * CoefA - CoefB;
            if (value > 255)
                value = 255;
            if (value < 0)
                value = 0;
            unsigned char index = floor(value);

            if(*wImReg)
            {
                wBitmap->rgbRed   = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbRed)/3;
                wBitmap->rgbGreen = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbGreen)/3;
                wBitmap->rgbBlue  = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbBlue)/3;
            }
            else
            {
                wBitmap->rgbRed   = (2* index)/3;
                wBitmap->rgbGreen = (2* index)/3;
                wBitmap->rgbBlue  = (2* index)/3;

            }
            wBitmap++;
            wImReg++;
            wIm16++;
        }
    }
}

//---------------------------------------------------------------------------
void MakeWhiteBitmap(Graphics::TBitmap *Bitmap)
{
	int width =  Bitmap->Width;
	int height = Bitmap->Height;

	Bitmap->PixelFormat = pf32bit;

	RGBQUAD Pixel;
	Pixel.rgbBlue = 255;
	Pixel.rgbGreen = 255;
	Pixel.rgbRed = 255;

	RGBQUAD *wBitmap;
	for (int y = 0; y < height; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < width; x++)
		{
			*wBitmap = Pixel;
			wBitmap++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowImage16(unsigned short *Im16, Graphics::TBitmap *Bitmap,
				 int maxX,int maxY, int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wIm16 = Im16;
	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{

			float value = *wIm16 * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			unsigned char index = floor(value);

			wBitmap->rgbRed   = index;
			wBitmap->rgbGreen = index;
			wBitmap->rgbBlue  = index;

			wBitmap++;
			wIm16++;
		}
	}
}

//---------------------------------------------------------------------------
void ShowPartOfImage16PseudoColor(unsigned short *Im16, Graphics::TBitmap *Bitmap,
								  int maxX,int maxY, int minVal, int maxVal,
								  int centerX, int centerY, int windowX ,int windowY)
{
	if(Bitmap->Height != windowY)
		Bitmap->Height = windowY;
	if(Bitmap->Width != windowX)
		Bitmap->Width = windowX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	int halfX = windowX/2;
	int halfY = windowY/2;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wIm16 = Im16;
	RGBQUAD *wBitmap;

	for (int y = 0; y < windowY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		int bigY = centerY - halfY + y;
		wIm16 = Im16 + bigY * maxX + centerX - halfX;
		for (int x = 0; x < windowX; x++)
		{
			int bigX = centerX - halfX + x;
			if(bigY >= 0 && bigY < maxY && bigX >= 0 && bigX < maxX)
			{
				float value = (float)(*wIm16) * CoefA - CoefB;
				if (value > 255)
					value = 255;
				if (value < 0)
					value = 0;
				unsigned char index = floor(value);

				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = outOfImageRed;
				wBitmap->rgbGreen = outOfImageGreen;
				wBitmap->rgbBlue  = outOfImageBlue;
			}
			wBitmap++;
			wIm16++;
		}
	}
}

//---------------------------------------------------------------------------
void ShowRegionOnImage16(unsigned short *ImReg, unsigned short *Im16,
						 Graphics::TBitmap *Bitmap, int maxX,int maxY,
						 int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wImReg = ImReg;
	unsigned short *wIm16 = Im16;

	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{
			float value = *wIm16 * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			unsigned char index = floor(value);

			if(*wImReg)
			{
				wBitmap->rgbRed   = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbRed)/3;
				wBitmap->rgbGreen = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbGreen)/3;
				wBitmap->rgbBlue  = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbBlue)/3;
			}
			else
			{
				wBitmap->rgbRed   = (2* index)/3;
				wBitmap->rgbGreen = (2* index)/3;
				wBitmap->rgbBlue  = (2* index)/3;

			}
			wBitmap++;
			wImReg++;
			wIm16++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowRegionOnImage16PseudoColor(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg)
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 255;
				wBitmap->rgbGreen = 255;
				wBitmap->rgbBlue  = 255;
			}
			wBitmap++;
			wImReg++;
			wIm16++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowPartRegionOnImage16(unsigned short *ImReg, unsigned short *Im16,
						 Graphics::TBitmap *Bitmap,
						 int maxX,int maxY, int minVal, int maxVal,
						 int centerX, int centerY, int windowX ,int windowY)
{
	if(Bitmap->Height != windowY)
		Bitmap->Height = windowY;
	if(Bitmap->Width != windowX)
		Bitmap->Width = windowX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	int halfX = windowX/2;
	int halfY = windowY/2;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wImReg = ImReg;
	unsigned short *wIm16 = Im16;

	RGBQUAD *wBitmap;

	for (int y = 0; y < windowY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		int bigY = centerY - halfY + y;
		wImReg = ImReg + bigY * maxX + centerX - halfX;
		wIm16 = Im16 + bigY * maxX + centerX - halfX;

		for (int x = 0; x < windowX; x++)
		{
			int bigX = centerX - halfX + x;
			if(bigY >= 0 && bigY < maxY && bigX >= 0 && bigX < maxX)
			{
				float value = *wIm16 * CoefA - CoefB;
				if (value > 255)
					value = 255;
				if (value < 0)
					value = 0;
				unsigned char index = floor(value);

				if(*wImReg)
				{
					wBitmap->rgbRed   = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbRed)/3;
					wBitmap->rgbGreen = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbGreen)/3;
					wBitmap->rgbBlue  = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbBlue)/3;
				}
				else
				{
					wBitmap->rgbRed   = (2* index)/3;
					wBitmap->rgbGreen = (2* index)/3;
					wBitmap->rgbBlue  = (2* index)/3;
				}
			}
			else
			{
				wBitmap->rgbRed   = outOfImageRed;
				wBitmap->rgbGreen = outOfImageGreen;
				wBitmap->rgbBlue  = outOfImageBlue;
			}
			wBitmap++;
			wImReg++;
			wIm16++;
		}
	}

}
//---------------------------------------------------------------------------
void ShowPartRegionOnImage16PseudoColor(unsigned short *ImReg, unsigned short *Im16,
						 Graphics::TBitmap *Bitmap,
						 int maxX,int maxY, int minVal, int maxVal,
						 int centerX, int centerY, int windowX ,int windowY)
{
	if(Bitmap->Height != windowY)
		Bitmap->Height = windowY;
	if(Bitmap->Width != windowX)
		Bitmap->Width = windowX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	int halfX = windowX/2;
	int halfY = windowY/2;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wImReg = ImReg;
	unsigned short *wIm16 = Im16;

	RGBQUAD *wBitmap;

	for (int y = 0; y < windowY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		int bigY = centerY - halfY + y;
		wImReg = ImReg + bigY * maxX + centerX - halfX;
		wIm16 = Im16 + bigY * maxX + centerX - halfX;

		for (int x = 0; x < windowX; x++)
		{
			int bigX = centerX - halfX + x;
			if(bigY >= 0 && bigY < maxY && bigX >= 0 && bigX < maxX)
			{


				float value = (float)(*wIm16) * CoefA - CoefB;
				if (value > 255)
					value = 255;
				if (value < 0)
					value = 0;
				int index = floor(value);

				if(!*wImReg)
				{
					wBitmap->rgbRed   = colormapR[index];
					wBitmap->rgbGreen = colormapG[index];
					wBitmap->rgbBlue  = colormapB[index];
				}
				else
				{
					wBitmap->rgbRed   = 50;
					wBitmap->rgbGreen = 50;
					wBitmap->rgbBlue  = 50;
				}
			}
			else
			{
				wBitmap->rgbRed   = outOfImageRed;
				wBitmap->rgbGreen = outOfImageGreen;
				wBitmap->rgbBlue  = outOfImageBlue;
			}
			wBitmap++;
			wImReg++;
			wIm16++;
		}
	}

}


//---------------------------------------------------------------------------
void ShowPartRegion(unsigned short *ImReg, Graphics::TBitmap *Bitmap,
						 int maxX,int maxY,
						 int centerX, int centerY, int windowX ,int windowY)
{
	if(Bitmap->Height != windowY)
		Bitmap->Height = windowY;
	if(Bitmap->Width != windowX)
		Bitmap->Width = windowX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	int halfX = windowX/2;
	int halfY = windowY/2;

	unsigned short *wImReg = ImReg;

	RGBQUAD *wBitmap;

	for (int y = 0; y < windowY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		int bigY = centerY - halfY + y;
		wImReg = ImReg + bigY * maxX + centerX - halfX;
		for (int x = 0; x < windowX; x++)
		{
			int bigX = centerX - halfX + x;
			if(bigY >= 0 && bigY < maxY && bigX >= 0 && bigX < maxX)
			{
				if(*wImReg)
				{
					wBitmap->rgbRed   = RegColorsRGBQ[(*wImReg%16)-1].rgbRed;
					wBitmap->rgbGreen = RegColorsRGBQ[(*wImReg%16)-1].rgbGreen;
					wBitmap->rgbBlue  = RegColorsRGBQ[(*wImReg%16)-1].rgbBlue;
				}
				else
				{
					wBitmap->rgbRed   = 0;
					wBitmap->rgbGreen = 0;
					wBitmap->rgbBlue  = 0;
				}
			}
			else
			{
				wBitmap->rgbRed   = outOfImageRed;
				wBitmap->rgbGreen = outOfImageGreen;
				wBitmap->rgbBlue  = outOfImageBlue;
			}
			wBitmap++;
			wImReg++;
		}
	}

}
//---------------------------------------------------------------------------
void ShowRegionSpecial(unsigned short *ImReg, Graphics::TBitmap *Bitmap,
						 int maxX,int maxY)
// Special meaning of few regions
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	unsigned short *wImReg = ImReg;

	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wImReg = ImReg + y * maxX;
		for (int x = 0; x < maxX; x++)
		{
			switch(*wImReg)
			{
				case 0:
					wBitmap->rgbRed   = 0;
					wBitmap->rgbGreen = 0;
					wBitmap->rgbBlue  = 0;
					break;

				case 0xFFFF:
					wBitmap->rgbRed   = 100;
					wBitmap->rgbGreen = 100;
					wBitmap->rgbBlue  = 100;
					break;
				case 0xFFFE:
					wBitmap->rgbRed   = 200;
					wBitmap->rgbGreen = 200;
					wBitmap->rgbBlue  = 200;
					break;

				case 0xFFFD:
					wBitmap->rgbRed   = 50;
					wBitmap->rgbGreen = 50;
					wBitmap->rgbBlue  = 50;
					break;

				case 0xFFFC:
					wBitmap->rgbRed   = 50;
					wBitmap->rgbGreen = 50;
					wBitmap->rgbBlue  = 50;
					break;

				default:
					wBitmap->rgbRed   = RegColorsRGBQ[(*wImReg%16)-1].rgbRed;
					wBitmap->rgbGreen = RegColorsRGBQ[(*wImReg%16)-1].rgbGreen;
					wBitmap->rgbBlue  = RegColorsRGBQ[(*wImReg%16)-1].rgbBlue;
					break;
			}
			wBitmap++;
			wImReg++;
		}
	}

}
//---------------------------------------------------------------------------
void ShowImageFloatPseudoColor(float *ImIn, Graphics::TBitmap *Bitmap,
							   int maxX,int maxY, float minVal, float maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;

	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;


	float *wImIn = ImIn;
	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{

			float value = *wImIn * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			int index = floor(value);

			wBitmap->rgbRed   = colormapR[index];
			wBitmap->rgbGreen = colormapG[index];
			wBitmap->rgbBlue  = colormapB[index];

			wBitmap++;
			wImIn++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowPartImageFloatPseudoColor(float *ImIn, Graphics::TBitmap *Bitmap,
								   int maxX,int maxY, float minVal, float maxVal,
								   int centerX, int centerY, int windowX ,int windowY)
{

	int halfX = windowX/2;
	int halfY = windowY/2;

	if(Bitmap->Height != windowY)
		Bitmap->Height = windowY;
	if(Bitmap->Width != windowX)
		Bitmap->Width = windowX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;

	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;


	float *wImIn = ImIn;
	RGBQUAD *wBitmap;

	for (int y = 0; y < windowY; y++)
	{
		int bigY = centerY - halfY + y;
		wImIn = ImIn + bigY * maxX + centerX - halfX;
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < windowX; x++)
		{

			int bigX = centerX - halfX + x;
			if(bigY >= 0 && bigY < maxY && bigX >= 0 && bigX < maxX)
			{
				float value = *wImIn * CoefA - CoefB;
				if (value > 255)
					value = 255;
				if (value < 0)
					value = 0;
				int index = floor(value);

				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = outOfImageRed;
				wBitmap->rgbGreen = outOfImageGreen;
				wBitmap->rgbBlue  = outOfImageBlue;
			}
			wBitmap++;
			wImIn++;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ShowPseudoColorScale(TImage *Im)
{
	int scaleImWidth = Im->Width;
	Graphics::TBitmap *TempBMP = new Graphics::TBitmap();
	RGBQUAD *wTempBMP;
	TempBMP->Height = 256;
	TempBMP->Width = scaleImWidth;
	TempBMP->PixelFormat = pf32bit;

	int index;
	for (int y = 0; y <= 255; y++)
	{
		wTempBMP = (RGBQUAD *)TempBMP->ScanLine[y];
		for (int x = 0; x<scaleImWidth; x++)
		{
			wTempBMP->rgbRed   = colormapR[255-y];
			wTempBMP->rgbGreen = colormapG[255-y];
			wTempBMP->rgbBlue  = colormapB[255-y];
			wTempBMP++;
		}
	}
	Im->Picture->Bitmap->Assign(TempBMP);
	delete TempBMP;
}
//---------------------------------------------------------------------------
void ShowPseudoColorScale64x256(TImage *Im,int min, int max)
{
	Graphics::TBitmap *Bmp = new Graphics::TBitmap;
	Bmp->Width = 64;
	Bmp->Height = 256;
	Bmp->PixelFormat = pf32bit;
	MakeWhiteBitmap(Bmp);

	RGBQUAD *wBmp;
	int index;
	for (int y = 0; y <= 255; y++)
	{
		wBmp = (RGBQUAD *)Bmp->ScanLine[y];
		for (int x = 0; x<16; x++)
		{
			wBmp->rgbRed   = colormapR[255-y];
			wBmp->rgbGreen = colormapG[255-y];
			wBmp->rgbBlue  = colormapB[255-y];
			wBmp++;
		}
	}
	Bmp->Canvas->Pen->Color = clBlack;

	int coef = (max - min)/4  ;
	Bmp->Canvas->MoveTo(20,255);
	Bmp->Canvas->LineTo(25,255);
	Bmp->Canvas->TextOutA(25,244,FormatFloat(" ## ##0",min));
	Bmp->Canvas->MoveTo(20,191);
	Bmp->Canvas->LineTo(25,191);
	Bmp->Canvas->TextOutA(25,184,FormatFloat(" ## ##0",min + coef * 1));
	Bmp->Canvas->MoveTo(20,127);
	Bmp->Canvas->LineTo(25,127);
	Bmp->Canvas->TextOutA(25,120,FormatFloat(" ## ##0",min + coef * 2));
	Bmp->Canvas->MoveTo(20,63);
	Bmp->Canvas->LineTo(25,63);
	Bmp->Canvas->TextOutA(25,56,FormatFloat(" ## ##0",min + coef * 3));

	Bmp->Canvas->MoveTo(20,0);
	Bmp->Canvas->LineTo(25,0);
	Bmp->Canvas->TextOutA(25,0,FormatFloat("## ##0",max));

	Im->Picture->Bitmap->Assign(Bmp);
	delete Bmp;
}
//---------------------------------------------------------------------------
void ShowHistVertLine(TImage *ImOut,int position, int color)
{
	int width =  ImOut->Width;
	int height =  ImOut->Height;



	int x = position * width / 4096;

	ImOut->Canvas->Pen->Color = (TColor)RegColorsRGB[color];
	ImOut->Canvas->MoveTo(x,0);
	ImOut->Canvas->LineTo(x,height);
}
//---------------------------------------------------------------------------
void ShowHistHorLine(TImage *ImOut,int position, int color)
{
	//int width =  ImOut->Width;
	int height =  ImOut->Height;
	int maxX = ImOut->Width - 1;
	int maxY = ImOut->Height - 1;

	int y = maxY - position * height / 4096;
	if(y > maxY)
		y = maxY;
	if(y < 0)
		y = 0;

	ImOut->Canvas->Pen->Color = (TColor)RegColorsRGB[color];
	ImOut->Canvas->MoveTo(0,y);
	ImOut->Canvas->LineTo(maxX,y);
}

//---------------------------------------------------------------------------
void ShowHistVertScale(TImage *ImOut, int scaleHeight )
{
	int width =  40;
	int border = 8;
	int height =  scaleHeight + 2 * border;

	//temp Bitmap
	Graphics::TBitmap *ImTemp = new Graphics::TBitmap();
	ImTemp->Height = height;
	ImTemp->Width = width;
	ImTemp->PixelFormat = pf32bit;

	// white image creation
	RGBQUAD Pixel;
	Pixel.rgbBlue = 255;
	Pixel.rgbGreen = 255;
	Pixel.rgbRed = 255;

	RGBQUAD *wImTemp;
	for (int y = 0; y < height; y++)
	{
		wImTemp = (RGBQUAD *)ImTemp->ScanLine[y];
		for (int x = 0; x < width; x++)
		{
			*wImTemp = Pixel;
			wImTemp++;
		}
	}
	//
	int histGridStep = 32;
	int histNrStep = 128;

	int scaleGridStep = histGridStep * scaleHeight /4096;
	int scaleNrStep = histNrStep * scaleHeight /4096;

	int y0 = scaleHeight + border;

	ImOut->Canvas->Pen->Color = clBlack;
	for(int i = 0; i <= scaleHeight; i+=scaleGridStep)
	{
		ImTemp->Canvas->MoveTo(0,y0-i);
		ImTemp->Canvas->LineTo(8,y0-i);
	}
	for(int i = 0; i <= scaleHeight; i+=scaleNrStep)
	{
		AnsiString Temp = FormatFloat("0",i*4096/scaleHeight);
		ImTemp->Canvas->TextOutA(10,y0-i-6,Temp);
	}

	ImOut->Picture->Bitmap->Assign(ImTemp);
	delete ImTemp;
}
//---------------------------------------------------------------------------
void ShowHistHorScale(TImage *ImOut, int scaleWidth )
{
	int height =  30;
	int border = 8;
	int width =  scaleWidth + 4 * border;

	//temp Bitmap
	Graphics::TBitmap *ImTemp = new Graphics::TBitmap();
	ImTemp->Height = height;
	ImTemp->Width = width;
	ImTemp->PixelFormat = pf32bit;

	// white image creation
	RGBQUAD Pixel;
	Pixel.rgbBlue = 255;
	Pixel.rgbGreen = 255;
	Pixel.rgbRed = 255;

	RGBQUAD *wImTemp;
	for (int y = 0; y < height; y++)
	{
		wImTemp = (RGBQUAD *)ImTemp->ScanLine[y];
		for (int x = 0; x < width; x++)
		{
			*wImTemp = Pixel;
			wImTemp++;
		}
	}
	//
	int histGridStep = 256;
	int histNrStep = 512;

	int scaleGridStep = histGridStep * scaleWidth /4096;
	int scaleNrStep = histNrStep * scaleWidth /4096;

	int x0 = border;

	ImOut->Canvas->Pen->Color = clBlack;
	for(int i = 0; i <= scaleWidth; i+=scaleGridStep)
	{
		ImTemp->Canvas->MoveTo(x0 + i,0);
		ImTemp->Canvas->LineTo(x0 + i,8);
	}
	for(int i = 0; i <= scaleWidth; i+=scaleNrStep)
	{
		AnsiString Temp = FormatFloat("0",i*4096/scaleWidth);
		int charCount = Temp.Length();
		for(int i =  charCount; i < 4; i++)
			Temp = " " + Temp;
		ImTemp->Canvas->TextOutA(x0 + i-8,15,Temp);
	}
	ImOut->Picture->Bitmap->Assign(ImTemp);
	delete ImTemp;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ShowImage8(unsigned char *Im8, Graphics::TBitmap *Bitmap,
				 int maxX,int maxY, int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned char *wIm8 = Im8;
	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{

			float value = *wIm8 * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			unsigned char index = floor(value);

			wBitmap->rgbRed   = index;
			wBitmap->rgbGreen = index;
			wBitmap->rgbBlue  = index;

			wBitmap++;
			wIm8++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowImage8PseudoColor(unsigned char *Im8, Graphics::TBitmap *Bitmap,
							int maxX,int maxY, int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned char *wIm8 = Im8;
	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{

			value = (float)(*wIm8) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			wBitmap->rgbRed   = colormapR[index];
			wBitmap->rgbGreen = colormapG[index];
			wBitmap->rgbBlue  = colormapB[index];

			wBitmap++;
			wIm8++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowRegionOnImage8(unsigned short *ImReg, unsigned char *Im8,
						 Graphics::TBitmap *Bitmap, int maxX,int maxY,
						 int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wImReg = ImReg;
	unsigned char *wIm8 = Im8;

	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{
			float value = *wIm8 * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			unsigned char index = floor(value);

			if(*wImReg)
			{
				wBitmap->rgbRed   = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbRed)/3;
				wBitmap->rgbGreen = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbGreen)/3;
				wBitmap->rgbBlue  = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbBlue)/3;
			}
			else
			{
				wBitmap->rgbRed   = (2* index)/3;
				wBitmap->rgbGreen = (2* index)/3;
				wBitmap->rgbBlue  = (2* index)/3;

			}
			wBitmap++;
			wImReg++;
			wIm8++;
		}
	}
}
//---------------------------------------------------------------------------
void ShowRegionOnImage8Specjal(unsigned short *ImReg, unsigned char *Im8,
						 Graphics::TBitmap *Bitmap, int maxX,int maxY,
						 int minVal, int maxVal)
{
	if(Bitmap->Height != maxY)
		Bitmap->Height = maxY;
	if(Bitmap->Width != maxX)
		Bitmap->Width = maxX;
	if(Bitmap->PixelFormat != pf32bit)
		Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;

	unsigned short *wImReg = ImReg;
	unsigned char *wIm8 = Im8;

	RGBQUAD *wBitmap;

	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{
			float value = *wIm8 * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			unsigned char index = floor(value);

			switch(*wImReg)
			{
				case 0:
					wBitmap->rgbRed   = (2* index)/3;
					wBitmap->rgbGreen = (2* index)/3;
					wBitmap->rgbBlue  = (2* index)/3;
					break;

				case 0xFFFF:
					wBitmap->rgbRed   = 100;
					wBitmap->rgbGreen = 100;
					wBitmap->rgbBlue  = 100;
					break;
				case 0xFFFE:
					wBitmap->rgbRed   = 200;
					wBitmap->rgbGreen = 200;
					wBitmap->rgbBlue  = 200;
					break;

				case 0xFFFD:
					wBitmap->rgbRed   = 50;
					wBitmap->rgbGreen = 50;
					wBitmap->rgbBlue  = 50;
					break;

				case 0xFFFC:
					wBitmap->rgbRed   = 50;
					wBitmap->rgbGreen = 50;
					wBitmap->rgbBlue  = 50;
					break;

				default:
					wBitmap->rgbRed   = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbRed)/3;
					wBitmap->rgbGreen = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbGreen)/3;
					wBitmap->rgbBlue  = (2* index + RegColorsRGBQ[(*wImReg%16)-1].rgbBlue)/3;
					break;
			}
			wBitmap++;
			wImReg++;
			wIm8++;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ShowRegionOnImage(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	Bitmap->Height = maxY;
	Bitmap->Width = maxX;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	for (int y = 0; y < maxY; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{
			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg)
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 50;
				wBitmap->rgbGreen = 50;
				wBitmap->rgbBlue  = 50;
			}
			wBitmap++;
			wImReg++;
			wIm16++;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ShowRegioOnZoomed3Image(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 3;
	int maxY3 = maxY * 3;
	Bitmap->Height = maxY * 3;
	Bitmap->Width = maxX * 3;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int i;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/3*maxX;
		wImReg = ImReg + y/3*maxX;
		i = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg)
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 50;
				wBitmap->rgbGreen = 50;
				wBitmap->rgbBlue  = 50;
			}
			wBitmap++;
			i++;
			if(i>2)
			{
				i = 0;
				wImReg++;
				wIm16++;
			}
		}
	}
}
//---------------------------------------------------------------------------
void ShowRegioOnZoomed3ImageOnePixel(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 3;
	int maxY3 = maxY * 3;
	Bitmap->Height = maxY * 3;
	Bitmap->Width = maxX * 3;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/3*maxX;
		wImReg = ImReg + y/3*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || (xL != 1 || yL !=1))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>2)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>2)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowContourOnZoomed3Image(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 3;
	int maxY3 = maxY * 3;
	Bitmap->Height = maxY * 3;
	Bitmap->Width = maxX * 3;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	unsigned short *wImReg1 = ImReg - maxX - 1;
	unsigned short *wImReg2 = ImReg - maxX;
	unsigned short *wImReg3 = ImReg - maxX + 1;
	unsigned short *wImReg4 = ImReg - 1;
	unsigned short *wImReg5 = ImReg + 1;
	unsigned short *wImReg6 = ImReg + maxX - 1;
	unsigned short *wImReg7 = ImReg + maxX;
	unsigned short *wImReg8 = ImReg + maxX + 1;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/3*maxX;
		wImReg = ImReg + y/3*maxX;
		wImReg1 = ImReg + y/3*maxX - maxX - 1;
		wImReg2 = ImReg + y/3*maxX - maxX;
		wImReg3 = ImReg + y/3*maxX - maxX + 1;
		wImReg4 = ImReg + y/3*maxX - 1;
		wImReg5 = ImReg + y/3*maxX + 1;
		wImReg6 = ImReg + y/3*maxX + maxX - 1;
		wImReg7 = ImReg + y/3*maxX + maxX;
		wImReg8 = ImReg + y/3*maxX + maxX + 1;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if((*wImReg && xL == 1 && yL ==1) ||
			   (*wImReg && *wImReg1 && xL == 0 && yL ==0) ||
			   (*wImReg && *wImReg2 && xL == 1 && yL ==0) ||
			   (*wImReg && *wImReg3 && xL == 2 && yL ==0) ||
			   (*wImReg && *wImReg4 && xL == 0 && yL ==1) ||
			   (*wImReg && *wImReg5 && xL == 2 && yL ==1) ||
			   (*wImReg && *wImReg6 && xL == 0 && yL ==2) ||
			   (*wImReg && *wImReg7 && xL == 1 && yL ==2) ||
			   (*wImReg && *wImReg8 && xL == 2 && yL ==2) )
			{

				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			else
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			wBitmap++;
			xL++;
			if(xL>2)
			{
				xL = 0;
				wImReg++;
				wImReg1++;
				wImReg2++;
				wImReg3++;
				wImReg4++;
				wImReg5++;
				wImReg6++;
				wImReg7++;
				wImReg8++;
				wIm16++;
			}
		}
		yL++;
		if(yL>2)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowRegioOnZoomed5ImageOnePixel(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || (xL != 2 || yL !=2))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowRegioOnZoomed5Image4Pixels(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || ((xL != 2 || yL !=1)
						&& (xL != 2 || yL !=3)
						&& (xL != 1 || yL !=2)
						&& (xL != 3 || yL !=2)))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowRegioOnZoomed5Image5Pixels(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || ((xL != 2 || yL !=1)
						&& (xL != 2 || yL !=2)
						&& (xL != 2 || yL !=3)
						&& (xL != 1 || yL !=2)
						&& (xL != 3 || yL !=2)))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}//---------------------------------------------------------------------------
void ShowRegioOnZoomed5Image9Pixels(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || (xL != 2 && yL !=2))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowRegioOnZoomed5ImageBorder(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;
	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if(!*wImReg || (xL != 0 && xL != 4 && yL != 0 && yL != 4))
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			else
			{
				wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
void ShowContourOnZoomed5Image(unsigned short *ImReg, unsigned short *Im16,
									Graphics::TBitmap *Bitmap,
									int maxX,int maxY, int minVal, int maxVal)
{
	int maxX3 = maxX * 5;
	int maxY3 = maxY * 5;
	Bitmap->Height = maxY * 5;
	Bitmap->Width = maxX * 5;
	Bitmap->PixelFormat = pf32bit;

	float difference = maxVal - minVal;
	if(difference == 0)
		difference = 1;
	float CoefA = 255/difference;
	float CoefB = CoefA * minVal;
	float value;
	unsigned char index;

	unsigned short *wIm16 = Im16;
	unsigned short *wImReg = ImReg;

	unsigned short *wImReg1 = ImReg - maxX - 1;
	unsigned short *wImReg2 = ImReg - maxX;
	unsigned short *wImReg3 = ImReg - maxX + 1;
	unsigned short *wImReg4 = ImReg - 1;
	unsigned short *wImReg5 = ImReg + 1;
	unsigned short *wImReg6 = ImReg + maxX - 1;
	unsigned short *wImReg7 = ImReg + maxX;
	unsigned short *wImReg8 = ImReg + maxX + 1;

	RGBQUAD *wBitmap;
	int xL,yL;
	yL = 0;
	for (int y = 0; y < maxY3; y++)
	{
		wBitmap = (RGBQUAD *)Bitmap->ScanLine[y];
		wIm16 = Im16 + y/5*maxX;
		wImReg = ImReg + y/5*maxX;

		wImReg1 = ImReg + y/5*maxX - maxX - 1;
		wImReg2 = ImReg + y/5*maxX - maxX;
		wImReg3 = ImReg + y/5*maxX - maxX + 1;
		wImReg4 = ImReg + y/5*maxX - 1;
		wImReg5 = ImReg + y/5*maxX + 1;
		wImReg6 = ImReg + y/5*maxX + maxX - 1;
		wImReg7 = ImReg + y/5*maxX + maxX;
		wImReg8 = ImReg + y/5*maxX + maxX + 1;


		xL = 0;
		for (int x = 0; x < maxX3; x++)
		{

			value = (float)(*wIm16) * CoefA - CoefB;
			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;
			index = floor(value);

			if((*wImReg && xL == 2 && yL ==2) ||
			   (*wImReg && *wImReg1 && xL == 0 && yL ==0) ||
			   (*wImReg && *wImReg1 && xL == 1 && yL ==1) ||
			   (*wImReg && *wImReg2 && xL == 2 && yL ==0) ||
			   (*wImReg && *wImReg2 && xL == 2 && yL ==1) ||
			   (*wImReg && *wImReg3 && xL == 4 && yL ==0) ||
			   (*wImReg && *wImReg3 && xL == 3 && yL ==1) ||
			   (*wImReg && *wImReg4 && xL == 0 && yL ==2) ||
			   (*wImReg && *wImReg4 && xL == 1 && yL ==2) ||
			   (*wImReg && *wImReg5 && xL == 4 && yL ==2) ||
			   (*wImReg && *wImReg5 && xL == 3 && yL ==2) ||
			   (*wImReg && *wImReg6 && xL == 0 && yL ==4) ||
			   (*wImReg && *wImReg6 && xL == 1 && yL ==3) ||
			   (*wImReg && *wImReg7 && xL == 2 && yL ==4) ||
			   (*wImReg && *wImReg7 && xL == 2 && yL ==3) ||
			   (*wImReg && *wImReg8 && xL == 4 && yL ==4) ||
			   (*wImReg && *wImReg8 && xL == 3 && yL ==3) )
			{
             	wBitmap->rgbRed   = 0;
				wBitmap->rgbGreen = 0;
				wBitmap->rgbBlue  = 0;
			}
			else
			{
				wBitmap->rgbRed   = colormapR[index];
				wBitmap->rgbGreen = colormapG[index];
				wBitmap->rgbBlue  = colormapB[index];
			}
			wBitmap++;
			xL++;
			if(xL>4)
			{
				xL = 0;
				wImReg++;
				wIm16++;
				wImReg1++;
				wImReg2++;
				wImReg3++;
				wImReg4++;
				wImReg5++;
				wImReg6++;
				wImReg7++;
				wImReg8++;
			}
		}
		yL++;
		if(yL>4)
		{
			yL = 0;
		}

	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void MakeZoomedImage(unsigned short *ImIn, unsigned short *ImOut,
					 int maxX, int maxY, int magFactor)
{
	int maxY1 = maxY * magFactor;
	unsigned short *wImIn = ImIn;
	unsigned short *wImOut = ImOut;
	for(int y = 0 ; y < maxY1; y++)
	{
		wImIn = ImIn + y/magFactor * maxX;
		for(int x = 0 ; x < maxX; x++)
		{
			for(int x1 = 0; x1 < magFactor; x1++)
			{
				*wImOut = *wImIn;
				wImOut++;
			}
			wImIn++;
		}
    }
}
//---------------------------------------------------------------------------
void ShowUnsignedChar(unsigned char *Im8 ,Graphics::TBitmap *BitmapToShow,
						int maxX, int maxY)
{
	if(BitmapToShow->Height != maxY)
		BitmapToShow->Height = maxY;
	if(BitmapToShow->Width != maxX)
		BitmapToShow->Width = maxX;
	if(BitmapToShow->PixelFormat != pf32bit)
		BitmapToShow->PixelFormat = pf32bit;

	RGBQUAD *wBitmapToShow;
	unsigned char *wIm8 = Im8;

	register int index;
	for (int y = 0; y < maxY; y++)
	{
		wBitmapToShow = (RGBQUAD *)BitmapToShow->ScanLine[y];
		for (int x = 0; x < maxX; x++)
		{
			index = *wIm8;
			if (index > 255)
				index = 255;
			if (index < 0)
				index = 0;
			wBitmapToShow->rgbRed   = colormapR[index];
			wBitmapToShow->rgbGreen = colormapG[index];
			wBitmapToShow->rgbBlue  = colormapB[index];
			wBitmapToShow++;
			wIm8++;
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
*/
