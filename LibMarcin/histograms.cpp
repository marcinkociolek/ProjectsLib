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
    meanD = 0.0;
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
    {
        mean = sum/count;
        meanD = double(sum)/double(count);
    }
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
    {
        mean = sum/count;
        meanD = double(sum)/double(count);
    }
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
    {
        mean = sum/count;
        meanD = double(sum)/double(count);
    }
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

    histMax = max;
    histMin = min;

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
double HistogramInteger::GetStd()
{
    if (histSize == 0)
        return -1.0;
    if (count == 0)
        return -2.0;

    double sum = 0;
    for(int k = 0; k < histSize; k++)
    {
        double diff = meanD - double(k);
        sum += pow(diff, 2.0) * double(Histogram[k]);
    }

    return sqrt(sum/double(count));
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramInteger::GetMin()
{
    return min;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramInteger::GetMax()
{
    return max;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramInteger::GetCount()
{
    return count;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramInteger::GetMean()
{
    return mean;
}
//----------------------------------------------------------------------------------------------------------------
double HistogramInteger::GetMeanD()
{
    return meanD;
}
//----------------------------------------------------------------------------------------------------------------
string HistogramInteger::StatisticStringOut(string separator)
{
    string Out = "";
    Out += to_string(min);
    Out += separator;
    Out += to_string(max);
    Out += separator;
    Out += to_string(count);
    Out += separator;
    Out += to_string(meanD);
    Out += separator;
    Out += to_string(GetStd());
    Out += "\n";
    return Out;
}



//----------------------------------------------------------------------------------------------------------------
//Color
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//                private functions
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::Init()
{
    count = 0;

    minR = 255;
    maxR = 0;
    meanR = 0;
    maxPositionR = -1;

    minG = 255;
    maxG = 0;
    meanG = 0;
    maxPositionG = -1;

    minB = 255;
    maxB = 0;
    meanB = 0;
    maxPositionB = -1;
}
//----------------------------------------------------------------------------------------------------------------
int HistogramRGB::checkMat(cv::Mat Im)
{
    if(Im.empty())
        return 0;
    if(Im.channels() != 3)
        return -1;
    if(Im.type() != CV_8U)
        return -2;
    if((Im.cols * Im.rows) == 0)
        return -3;
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
int HistogramRGB::checkMat(cv::Mat Im, cv::Mat Mask)
{
    if(Im.empty())
        return 0;
    if(Im.channels() != 3)
        return -1;
    if(Im.type() != CV_8UC3)
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
void HistogramRGB::InitializeHistogram()
{
    HistogramR = new int[256];
    HistogramG = new int[256];
    HistogramB = new int[256];
    for(int k = 0; k < 256; k++)
    {
        HistogramR[k] = 0;
        HistogramG[k] = 0;
        HistogramB[k] = 0;
    }
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::BasicStaistics(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    int64_t sumR = 0;
    int64_t sumG = 0;
    int64_t sumB = 0;

    uint8_t *wIm;
    wIm = (uint8_t*)Im.data;
    for(int i = 0; i< maxXY; i++)
    {
        uint8_t b = *wIm;
        wIm++;
        uint8_t g = *wIm;
        wIm++;
        uint8_t r = *wIm;
        wIm++;


        if (maxB < b)
            maxB = b;
        if (minB > b)
            minB = b;
        sumB += b;

        if (maxG < g)
            maxG = g;
        if (minG > g)
            minG = g;
        sumG += g;

        if (maxR < r)
            maxR = r;
        if (minR > r)
            minR = r;
        sumR += r;

    }

    count = maxXY;
    if(count)
    {
        meanR = sumR/count;
        meanG = sumG/count;
        meanB = sumB/count;
    }
}
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::BasicStaistics(cv::Mat Im, cv::Mat Mask, int roiNr)
{
    int maxXY = Im.cols * Im.rows;

    int64_t sumR = 0;
    int64_t sumG = 0;
    int64_t sumB = 0;
    count = 0;

    uint8_t *wIm;
    uint16_t *wMask;
    wMask = (uint16_t*)Mask.data;
    wIm = (uint8_t*)Im.data;
    for(int i = 0; i< maxXY; i++)
    {
        uint8_t b = *wIm;
        wIm++;
        uint8_t g = *wIm;
        wIm++;
        uint8_t r = *wIm;
        wIm++;

        if(*wMask == roiNr || roiNr == 0)
        {
            if (maxB < b)
                maxB = b;
            if (minB > b)
                minB = b;
            sumB += b;

            if (maxG < g)
                maxG = g;
            if (minG > g)
                minG = g;
            sumG += g;

            if (maxR < r)
                maxR = r;
            if (minR > r)
                minR = r;
            sumR += r;

            count++;
        }
        wMask++;
    }

    if(count)
    {
        meanR = sumR/count;
        meanG = sumG/count;
        meanB = sumB/count;
    }
}

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::FindHistogram(cv::Mat Im)
{
    int maxXY = Im.cols * Im.rows;

    uint8_t *wIm = (uint8_t*)Im.data;

    for(int i = 0; i< maxXY; i++)
    {
        int64_t b = *wIm;
        wIm++;
        int64_t g = *wIm;
        wIm++;
        int64_t r = *wIm;
        wIm++;
        HistogramR[r]++;
        HistogramG[g]++;
        HistogramB[b]++;
    }
}
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::FindHistogram(cv::Mat Im, cv::Mat Mask, int roiNr)
{
    int maxXY = Im.cols * Im.rows;

    uint8_t *wIm = (uint8_t*)Im.data;
    uint16_t *wMask = (uint16_t*)Mask.data;

    for(int i = 0; i< maxXY; i++)
    {
        int64_t b = *wIm;
        wIm++;
        int64_t g = *wIm;
        wIm++;
        int64_t r = *wIm;
        wIm++;
        if(*wMask == roiNr || (roiNr == -1 && *wMask > 0))
        {
            HistogramR[r]++;
            HistogramG[g]++;
            HistogramB[b]++;
        }
        wMask++;
    }
}

//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::FindMaxPos()
{
   if (count == 0)
       return;
   int maxHist;
   int *wHist;

   maxHist = 0;
   wHist = HistogramB;
   for(int i = 0; i <255; i++)
   {
        if(maxHist < *wHist)
        {
            maxHist = *wHist;
            maxPositionB = i;
        }
        wHist++;
   }

   maxHist = 0;
   wHist = HistogramG;
   for(int i = 0; i <255; i++)
   {
        if(maxHist < *wHist)
        {
            maxHist = *wHist;
            maxPositionG = i;
        }
        wHist++;
   }

   maxHist = 0;
   wHist = HistogramR;
   for(int i = 0; i <255; i++)
   {
        if(maxHist < *wHist)
        {
            maxHist = *wHist;
            maxPositionR = i;
        }
        wHist++;
   }
}
//----------------------------------------------------------------------------------------------------------------
//                public functions
//----------------------------------------------------------------------------------------------------------------
HistogramRGB::HistogramRGB()
{
    Init();
    HistogramR = nullptr;
    HistogramG = nullptr;
    HistogramB = nullptr;
}
//----------------------------------------------------------------------------------------------------------------
HistogramRGB::~HistogramRGB()
{
    Release();
}
//----------------------------------------------------------------------------------------------------------------
void HistogramRGB::Release()
{
    delete[] HistogramR;
    HistogramR = nullptr;
    delete[] HistogramG;
    HistogramG = nullptr;
    delete[] HistogramB;
    HistogramB = nullptr;
    Init();
}
//----------------------------------------------------------------------------------------------------------------
int HistogramRGB::FromMat(Mat Im)
{
    Release();

    int check = checkMat(Im);
    if(check <= 0)
        return check;

    BasicStaistics(Im);

    InitializeHistogram();

    FindHistogram(Im);
    FindMaxPos();

    return 1;
}
//----------------------------------------------------------------------------------------------------------------
int HistogramRGB::FromMat(Mat Im, Mat Mask, int roiNr)
{
    Release();

    int check = checkMat(Im, Mask);
    if(check <= 0)
        return check;

    InitializeHistogram();
    BasicStaistics(Im, Mask, roiNr);



    FindHistogram(Im, Mask, roiNr);
    FindMaxPos();
    return 1;

}
//----------------------------------------------------------------------------------------------------------------
string HistogramRGB::GetString()
{
    string Out = "Param\tR\tG\tB\n";
    Out += " min = \t" + to_string(minR) + "\t" + to_string(minG) + "\t" + to_string(minB) + "\n";
    Out += " max = \t" + to_string(maxR) + "\t" + to_string(maxG) + "\t" + to_string(maxB) + "\n";
    Out += " mean = \t" + to_string(meanR) + "\t" + to_string(meanG) + "\t" + to_string(meanB) + "\n";
    Out += "\n";
    Out += "val \thist R \thist G\t hist B\n";
    for(int k = 0; k < 256; k++)
    {
        Out +=  to_string(k) + "\t" + to_string(HistogramR[k]) + "\t" + to_string(HistogramG[k]) + "\t" + to_string(HistogramB[k]) + "\n";
    }

    return Out;
}
//-----------------------------------------------------------------------------------------------------------

Mat HistogramRGB::Plot(int yScale, int scaleCoef, int barWidth , char colorPlane)
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

    int histSizeLocal = 256;
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
        string text = to_string(x);
        int nrOfdigits = (int)(text.size());
        putText(ImToShow,text,Point(leftOffset + x * (1 + barWidth)  - nrOfdigits * digitWidth / 2 ,
                                    yScaleHeight + topOffset + digitHeight * 2 + scaleBarLenht), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));
    }

    Point orygin = Point(leftOffset, yScaleHeight + topOffset);
    for(int bin = 0; bin < 256; bin++)
    {
        double histVal;
        switch(colorPlane)
        {
        case 'G':
            histVal = (double)HistogramG[bin];
            break;
        case 'B':
            histVal = (double)HistogramB[bin];
            break;
        default:
            histVal = (double)HistogramR[bin];
            break;
        }
        int barLenght = (int)round(histVal * pow(10.0,scaleCoef * (-1))*100);

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
//-----------------------------------------------------------------------------------------------------------

Mat HistogramRGB::PlotRGB(int yScale, int scaleCoef, int barWidth)
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

    int histSizeLocal = 256;
    if (histSizeLocal < 10)
        histSizeLocal = 10;


    int plotYSize = yScaleHeight + topOffset + bottomOffset;
    int plotXSize = leftOffset + rightOffset + histSizeLocal * ( 1 + barWidth * 3);
    cv::Mat ImToShow = Mat(plotYSize,plotXSize,CV_8UC3,cv::Scalar(255,255,255));


    line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),cv::Point(leftOffset - 2,topOffset),cv::Scalar(255.0,0.0,0.0,0.0));
    line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),Point(leftOffset + histSizeLocal *(1+barWidth*3),yScaleHeight + topOffset),Scalar(255.0,0.0,0.0,0.0));

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
    for(int x = 0; x <= histSizeLocal; x+= 32)
    {
        line(ImToShow,Point(leftOffset + x * (1 + barWidth * 3) + barWidth * 3 /2, yScaleHeight + topOffset),
                      Point(leftOffset + x * (1 + barWidth * 3) + barWidth * 3 /2,yScaleHeight + topOffset + scaleBarLenht),
                      Scalar(255.0,0.0,0.0,0.0));

        //std::ostringstream ss;
        //ss << std::fixed << std::setprecision(2) << (minValue + x * binRange);
        //std::string text = ss.str();
        string text = to_string(x);
        int nrOfdigits = (int)(text.size());
        putText(ImToShow,text,Point(leftOffset + x * (1 + barWidth * 3)  - nrOfdigits * digitWidth / 2 ,
                                    yScaleHeight + topOffset + digitHeight * 2 + scaleBarLenht), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));
    }

    Point orygin = Point(leftOffset, yScaleHeight + topOffset);
    for(int bin = 0; bin < 256; bin++)
    {
        int barLenght = (int)round((double)HistogramR[bin] * pow(10.0,scaleCoef * (-1))*100);

        Point start = orygin + Point(bin*(1 + barWidth*3), 0);

        if (barLenght > yScaleHeight)
        {
            barLenght = yScaleHeight;
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 0.0, 128.0, 0.0),CV_FILLED);
        }
        else
        {
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 0.0, 255.0, 0.0),CV_FILLED);
        }

        barLenght = (int)round((double)HistogramG[bin] * pow(10.0,scaleCoef * (-1))*100);

        start = orygin + Point(bin*(1 + barWidth*3) + barWidth, 0);
        if (barLenght > yScaleHeight)
        {
            barLenght = yScaleHeight;
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 128.0, 0.0, 0.0),CV_FILLED);
        }
        else
        {
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(0.0, 255.0, 0.0, 0.0),CV_FILLED);
        }
        barLenght = (int)round((double)HistogramB[bin] * pow(10.0,scaleCoef * (-1))*100);

        start = orygin + Point(bin*(1 + barWidth*3) + barWidth*2, 0);
        if (barLenght > yScaleHeight)
        {
            barLenght = yScaleHeight;
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(128.0, 0.0, 0.0, 0.0),CV_FILLED);
        }
        else
        {
            Point stop  = start + Point(barWidth - 1,0 - barLenght);
            rectangle(ImToShow,start,stop,Scalar(255.0, 0.0, 0.0, 0.0),CV_FILLED);
        }
    }
    return ImToShow;
}
//----------------------------------------------------------------------------------------------------------------
std::string StatisticStringHeader(std::string separator)
{
    string Out = "";
    Out += "min";
    Out += "\t";
    Out += "max";
    Out += "\t";
    Out += "count";
    Out += "\t";
    Out += "mean";
    Out += "\t";
    Out += "std";
    Out += "\n";
    return Out;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetCount()
{
    return count;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
double HistogramRGB::GetStdB()
{
    if (count == 0)
        return -2.0;
    double sum = 0;
    for(int k = 0; k < 256; k++)
    {
        double diff = meanB - double(k);
        sum += pow(diff, 2.0) * double(HistogramB[k]);
    }

    return sqrt(sum/double(count));
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMinB()
{
    return minB;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxB()
{
    return maxB;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMeanB()
{
    return meanB;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
double HistogramRGB::GetStdG()
{
    if (count == 0)
        return -2.0;

    double sum = 0;
    for(int k = 0; k < 256; k++)
    {
        double diff = meanG - double(k);
        sum += pow(diff, 2.0) * double(HistogramG[k]);
    }

    return sqrt(sum/double(count));
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMinG()
{
    return minG;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxG()
{
    return maxG;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMeanG()
{
    return meanG;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
double HistogramRGB::GetStdR()
{
    if (count == 0)
        return -2.0;

    double sum = 0;
    for(int k = 0; k < 256; k++)
    {
        double diff = meanR - double(k);
        sum += pow(diff, 2.0) * double(HistogramR[k]);
    }

    return sqrt(sum/double(count));
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMinR()
{
    return minR;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxR()
{
    return maxR;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMeanR()
{
    return meanR;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxPositionB()
{
    return maxPositionB;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxPositionG()
{
    return maxPositionG;
}
//----------------------------------------------------------------------------------------------------------------
int64_t HistogramRGB::GetMaxPositionR()
{
    return maxPositionR;
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
