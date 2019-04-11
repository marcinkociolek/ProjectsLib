#include "histograms.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
HistogramInteger::HistogramInteger()
{
    histMin = 0;
    histMax = 0;
    histSize = 0;
    min = 0xfffffffd;
    max = -0xfffffffe;
    mean = 0;
    Histogram = 0;
}
//----------------------------------------------------------------------------------------------------------------
HistogramInteger::~HistogramInteger()
{
    Release();
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::Release()
{
    histMin = 0;
    histMax = 0;
    histSize = 0;
    mean = 0;
    delete[] Histogram;
    Histogram = 0;
}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16U(Mat Im)
{
    Release();

    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_16U)
        return -2;


    int maxX = Im.cols;
    int maxY = Im.rows;
    int maxXY = maxX*maxY;

    if(maxXY == 0)
        return -3;

    uint16_t *wIm;
    wIm = (uint16_t*)Im.data;

    int sum = 0;
    max = 0;
    min = 65535;
    for(int i = 0; i< maxXY; i++)
    {
        if (max < *wIm)
            max = *wIm;
        if (min > *wIm)
            min = *wIm;

        sum += *wIm;
        wIm++;
    }

    mean = sum/maxXY;
    histMax = min;
    histMin = max;
    histSize = histMax - histMin + 1;
    Histogram = new int[histSize];
    for(int k = 0; k < histSize; k++)
    {
        Histogram[k] = 0;
    }

    wIm = (uint16_t*)Im.data;
    for(int i = 0; i< maxXY; i++)
    {
        int val = *wIm - histMin;
        if(val < 0)
            val = 0;
        if(val >= histSize)
            val = histSize - 1;
        Histogram[val]++;
        wIm++;
    }
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16U(Mat Im, Mat Mask, int roiNr)
{
    Release();

    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_16U)
        return -2;
    if(Mask.empty())
        return -3;
    if(Mask.channels() != 1)
        return -4;
    if(Mask.type() != CV_16U)
        return -5;

    if(Mask.cols != Im.cols)
        return -6;
    if(Mask.rows != Im.rows)
        return -7;


    int maxX = Im.cols;
    int maxY = Im.rows;
    int maxXY = maxX*maxY;

    if(maxXY == 0)
        return -3;

    uint16_t *wIm, *wMask;
    wIm = (uint16_t*)Im.data;
    wMask = (uint16_t*)Mask.data;
    int sum = 0;
    int count = 0;
    max = 0;
    min = 65535;
    for(int i = 0; i< maxXY; i++)
    {
        if(*wMask == roiNr || roiNr == 0)
        {
            if (max < *wIm)
                max = *wIm;
            if (min > *wIm)
                min = *wIm;
            sum += *wIm;
            count++;
        }
        wMask++;
        wIm++;
    }
    histMax = max;
    histMin = min;
    histSize = histMax - histMin + 1;
    if(count==0)
        count = 1;
    mean = sum/count;

    Histogram = new int[histSize];
    for(int k = 0; k < histSize; k++)
    {
        Histogram[k] = 0;
    }

    wIm = (uint16_t*)Im.data;
    wMask = (uint16_t*)Mask.data;
    for(int i = 0; i< maxXY; i++)
    {
        if(*wMask == roiNr || roiNr == 0)
        {
            int val = *wIm - histMin;
            if(val < 0)
                val = 0;
            if(val >= histSize)
                val = histSize - 1;
            Histogram[val]++;
        }
        wMask++;
        wIm++;
    }
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16ULimit(Mat Im, Mat Mask, int roiNr, int fixedMin, int fixedMax)
{
    Release();

    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_16U)
        return -2;
    if(Mask.empty())
        return -3;
    if(Mask.channels() != 1)
        return -4;
    if(Mask.type() != CV_16U)
        return -5;

    if(Mask.cols != Im.cols)
        return -6;
    if(Mask.rows != Im.rows)
        return -7;


    int maxX = Im.cols;
    int maxY = Im.rows;
    int maxXY = maxX*maxY;

    if(maxXY == 0)
        return -3;

    uint16_t *wIm, *wMask;
    wIm = (uint16_t*)Im.data;
    wMask = (uint16_t*)Mask.data;

    histMax = fixedMax;
    histMin = fixedMin;

    if(histMax > 65535)
        histMax = 65535;
    if(histMin < 0)
        histMin = 0;

    histSize = (histMax - histMin) + 1;

    if(histSize < 1)
        histSize = 1;
    Histogram = new int[histSize];
    for(int k = 0; k < histSize; k++)
    {
        Histogram[k] = 0;
    }

    wIm = (uint16_t*)Im.data;
    wMask = (uint16_t*)Mask.data;
    int sum = 0;
    int count = 0;
    min = 65535;
    max = 0;
    for(int i = 0; i< maxXY; i++)
    {
        if(*wMask == roiNr || roiNr == 0)
        {
            int intensity = *wIm;
            int val = intensity - histMin;
            if(val < 0)
                val = 0;
            if(val >= histSize)
                val = histSize - 1;
            Histogram[val]++;
            sum += intensity;
            count ++;
            if(min > intensity)
                min = intensity;
            if(max < intensity)
                max = intensity;
        }
        wMask++;
        wIm++;
    }
    if(count==0)
        count = 1;
    mean = sum/count;

    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat32S(Mat Im)
{
    Release();

    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return 0;
    if(Im.type() != CV_32S)
        return 0;


    int maxX = Im.cols;
    int maxY = Im.rows;
    int maxXY = maxX*maxY;

    int32_t *wIm;
    wIm = (int32_t*)Im.data;

    max = -0xfffffffe;
    min =  0xfffffffd;

    for(int i = 0; i< maxXY; i++)
    {
        if (max < *wIm)
            max = *wIm;
        if (min > *wIm)
            min = *wIm;
        wIm++;
    }
    histMax = max;
    histMin = min;
    histSize = histMax - histMin + 1;

    if(histSize < 65536)
    {
        Histogram = new int[histSize];
        for(int k = 0; k < histSize; k++)
        {
            Histogram[k] = 0;
        }

        wIm = (int32_t*)Im.data;
        for(int i = 0; i< maxXY; i++)
        {
            int val = *wIm - histMin;
            if(val < 0)
                val = 0;
            if(val >= histSize)
                val = histSize - 1;
            Histogram[val]++;
            wIm++;
        }
    }
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
string HistogramInteger::GetString()
{
    if (histSize == 0)
        return "Empty \n";

    string Out = "";
    Out += " hist min = \t" + to_string(histMin) + "\n";
    Out += " hist max = \t" + to_string(histMax) + "\n";
    Out += " size = \t" + to_string(histSize) + "\n";
    Out += " min = \t" + to_string(min) + "\n";
    Out += " max = \t" + to_string(max) + "\n";
    Out += " mean = \t" + to_string(mean) + "\n";
    Out += "\n";
    Out += "val \t hist\n";
    for(int k = 0; k < histSize; k++)
    {
        Out +=  to_string(k + histMin) + "\t" + to_string(Histogram[k]) + "\n";
    }

    return Out;
}
//-----------------------------------------------------------------------------------------------------------

Mat HistogramInteger::Plot(int yScale, int scaleCoef, int barWidth)
{
    const int topOffset = 30;
    const int bottomOffset = 30;
    const int scaleBarLenht = 5;
    const int leftOffset = 60;
    const int rightOffset = 20;
    const int digitWidth = 13;
    const int digitHeight = 10;

    //int binCount = numberOfBins;

    int yScaleHeight = 100 * yScale;

    int histSizeLocal = histSize;
    if (histSizeLocal < 10)
        histSizeLocal = 10;


    int plotYSize = yScaleHeight + topOffset + bottomOffset;
    int plotXSize = leftOffset + rightOffset + histSizeLocal * ( 1 + barWidth);
    cv::Mat ImToShow = Mat(plotYSize,plotXSize,CV_8UC3,cv::Scalar(255,255,255));


    line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),cv::Point(leftOffset - 2,topOffset),cv::Scalar(255.0,0.0,0.0,0.0));
    line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),Point(leftOffset + histSizeLocal *(1+barWidth),yScaleHeight + topOffset),Scalar(255.0,0.0,0.0,0.0));

    for(int y = 0; y <= yScaleHeight; y+= 100/2)
    {
        line(ImToShow,Point(leftOffset - scaleBarLenht,yScaleHeight + topOffset - y),Point(leftOffset-2 ,yScaleHeight + topOffset - y),Scalar(255.0,0.0,0.0,0.0));
    }
    for(int y = 0; y <= yScale; y++)
    {
        string text = to_string((int)round((double)y * pow(10.0,scaleCoef)));
        int nrOfdigits = (int)(text.size());
        putText(ImToShow,text,Point(leftOffset - scaleBarLenht -2 - nrOfdigits * digitWidth, yScaleHeight - y*100 + topOffset + digitHeight / 2), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));
    }
    for(int x = 0; x <= histSizeLocal; x+= 40)
    {
        line(ImToShow,Point(leftOffset + x * (1 + barWidth) + barWidth /2, yScaleHeight + topOffset),
                      Point(leftOffset + x * (1 + barWidth) + barWidth /2,yScaleHeight + topOffset + scaleBarLenht),
                      Scalar(255.0,0.0,0.0,0.0));

        //std::ostringstream ss;
        //ss << std::fixed << std::setprecision(2) << (minValue + x * binRange);
        //std::string text = ss.str();
        string text = to_string(histMin + x );
        int nrOfdigits = (int)(text.size());
        putText(ImToShow,text,Point(leftOffset + x * (1 + barWidth)  - nrOfdigits * digitWidth / 2 ,
                                    yScaleHeight + topOffset + digitHeight * 2 + scaleBarLenht), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));
    }

    Point orygin = Point(leftOffset, yScaleHeight + topOffset);
    for(int bin = 0; bin < histSize; bin++)
    {
        int barLenght = (int)round((double)Histogram[bin] * pow(10.0,scaleCoef * (-1))*100);

        Point start = orygin + Point(bin*(1 + barWidth), 0);
        if (barLenght > yScaleHeight)
        {
            barLenght = yScaleHeight;
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 0.0, 255.0, 0.0),CV_FILLED);
        }
        else
        {
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 0.0, 0.0, 0.0),CV_FILLED);
        }
    }
    return ImToShow;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
