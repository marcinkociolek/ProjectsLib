#include "histograms.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//                private functions
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::Init()
{
    histMin = 0;
    histMax = 0;
    histSize = 0;
    min = INT64_MAX;
    max = INT64_MIN;
    mean = 0;
    count = 0;
    binSize = 1;    
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::checkMat16U(cv::Mat Im)
{
    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_16U)
        return -2;
    if((Im.cols * Im.rows) == 0)
        return -3;
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::checkMat16U(cv::Mat Im, cv::Mat Mask)
{
    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_16U)
        return -2;
    if((Im.cols * Im.rows) == 0)
        return -3;

    if(Mask.empty())
        return -4;
    if(Mask.channels() != 1)
        return -5;
    if(Mask.type() != CV_16U)
        return -6;

    if(Mask.cols != Im.cols)
        return -7;
    if(Mask.rows != Im.rows)
        return -8;
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::checkMat32S(cv::Mat Im)
{
    if(Im.empty())
        return 0;
    if(Im.channels() != 1)
        return -1;
    if(Im.type() != CV_32S)
        return -2;
    if((Im.cols * Im.rows) == 0)
        return -3;
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::InitializeHistogram(int binS)
{
    binSize = binS;
    if(binSize < 1)
        binSize = 1;
    if(binSize > 256)
        binSize = 256;

    int64_t valueCount = histMax - histMin + 1;
    if((valueCount % binSize) == 0)
        histSize = valueCount/binSize;
    else
        histSize = valueCount/binSize+1;

    Histogram = new int[histSize];
    for(int k = 0; k < histSize; k++)
    {
        Histogram[k] = 0;
    }
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::BasicStaistics16U(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    int64_t sum = 0;

    uint16_t *wIm;
    wIm = (uint16_t*)Im.data;
    for(int i = 0; i< maxXY; i++)
    {
        if (max < *wIm)
            max = *wIm;
        if (min > *wIm)
            min = *wIm;

        sum += *wIm;
        wIm++;
    }

    count = maxXY;
    if(count)
        mean = sum/count;
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::BasicStaistics16U(cv::Mat Im, cv::Mat Mask, int roiNr)
{
    int maxXY = Im.cols * Im.rows;
    uint16_t *wIm, *wMask;
    wIm = (uint16_t*)Im.data;
    wMask = (uint16_t*)Mask.data;
    int64_t sum = 0;
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
    if(count)
        mean = sum/count;
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::BasicStaistics32S(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    int64_t sum = 0;

    int32_t *wIm = (int32_t*)Im.data;
    for(int i = 0; i< maxXY; i++)
    {
        if (max < *wIm)
            max = *wIm;
        if (min > *wIm)
            min = *wIm;

        sum += *wIm;
        wIm++;
    }

    count = maxXY;
    if(count)
        mean = sum/count;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::FindHistogram16U(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    uint16_t *wIm = (uint16_t*)Im.data;

    for(int i = 0; i< maxXY; i++)
    {
        int64_t val = (*wIm - histMin)/binSize;
        if(val < 0)
            val = 0;
        if(val >= histSize)
            val = histSize - 1;
        Histogram[val]++;
        wIm++;
    }
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::FindHistogram16U(cv::Mat Im, cv::Mat Mask, int roiNr)
{
    int maxXY = Im.cols * Im.rows;

    uint16_t *wIm = (uint16_t*)Im.data;
    uint16_t *wMask = (uint16_t*)Mask.data;

    for(int i = 0; i< maxXY; i++)
    {
        if(*wMask == roiNr || roiNr == 0)
        {
            int64_t val = (*wIm - histMin)/binSize;
            if(val < 0)
                val = 0;
            if(val >= histSize)
                val = histSize - 1;
            Histogram[val]++;
        }
        wMask++;
        wIm++;
    }
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::FindHistogram32S(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    int32_t *wIm = (int32_t*)Im.data;

    for(int i = 0; i< maxXY; i++)
    {
        int64_t val = (*wIm - histMin)/binSize;
        if(val < 0)
            val = 0;
        if(val >= histSize)
            val = histSize - 1;
        Histogram[val]++;
        wIm++;
    }
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//                public functions
//----------------------------------------------------------------------------------------------------------------
HistogramInteger::HistogramInteger()
{
    Init();
    Histogram = nullptr;
}
//----------------------------------------------------------------------------------------------------------------
HistogramInteger::~HistogramInteger()
{
    Release();
}
//----------------------------------------------------------------------------------------------------------------
void HistogramInteger::Release()
{
    delete[] Histogram;
    Histogram = nullptr;
    Init();
}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16U(Mat Im, int binS)
{
    Release();

    int check = checkMat16U(Im);
    if(check <= 0)
        return check;

    BasicStaistics16U(Im);

    histMax = min;
    histMin = max;

    InitializeHistogram(binS);

    FindHistogram16U(Im);

    return 1;
}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16U(Mat Im, Mat Mask, int roiNr, int binS)
{
    Release();

    int check = checkMat16U(Im);
    if(check <= 0)
        return check;

    BasicStaistics16U(Im, Mask, roiNr);

    histMax = max;
    histMin = min;

    InitializeHistogram(binS);

    FindHistogram16U(Im, Mask, roiNr);
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat16ULimit(Mat Im, Mat Mask, int roiNr, int fixedMin, int fixedMax, int binS)
{
    Release();

    int check = checkMat16U(Im);
    if(check <= 0)
        return check;

    BasicStaistics16U(Im, Mask, roiNr);

    histMax = fixedMax;
    histMin = fixedMin;

    if(histMax > 65535)
        histMax = 65535;
    if(histMin < 0)
        histMin = 0;

    if(histMax <= histMin)
        histMax = histMin + 1;

    InitializeHistogram(binS);

    FindHistogram16U(Im, Mask, roiNr);

    return 1;
}
//----------------------------------------------------------------------------------------------------------------
int HistogramInteger::FromMat32S(Mat Im, int binS)
{
    Release();

    int check = checkMat32S(Im);
    if(check <= 0)
        return check;

    BasicStaistics32S(Im);

    histMax = max;
    histMin = min;

    InitializeHistogram(binS);

    FindHistogram32S(Im);

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
        Out +=  to_string(k * binSize + histMin) + "\t" + to_string(Histogram[k]) + "\n";
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
        string text = to_string(histMin + x * binSize);
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
