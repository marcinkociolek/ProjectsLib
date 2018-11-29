#include "tileparams.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/core/core.hpp>
//#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

//#include <opencv2/core/core.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace boost;
using namespace cv;

TileParams::TileParams()
{
    tileY = -1;
    tileX = -1;;
    paramsCount = 0;
    Params.clear();
}

TileParams::~TileParams()
{
    tileY = -1;
    tileX = -1;;
    paramsCount = 0;
    Params.clear();
}


void TileParams::FromString(std::string InStr)
{
    std::stringstream InStringStream(InStr);

    std::string subStr;

    InStringStream >> subStr;
    if(subStr == "")
        return;
    tileY = std::stoi(subStr);
    InStringStream >> subStr;
    if(subStr == "")
        return;
    tileX = std::stoi(subStr);
    //std::vector<double> ParamsVector;
    while(InStringStream >> subStr)
    {
        paramsCount++;
        if(subStr == "NAN")
            Params.push_back(-1000.0);
        else
            Params.push_back(stof(subStr));
    }
    Params.push_back(0);
}


 FileParams::FileParams()
 {
     ImFileName = "";
     ImFolderName = "";
     tileShape = -1;
     tileSize = -1;
     ValueCount = 0;
     NamesVector.clear();
     ParamsVect.clear();
 }

 FileParams::~FileParams()
 {
     ImFileName.clear();
     ImFolderName.clear();
     tileShape = -1;
     tileSize = -1;
     ValueCount = 0;
     NamesVector.clear();
     ParamsVect.clear();
 }
 //-----------------------------------------------------------------------------------------------------------
 void IntensityStatistics::SaveToFile(string Filename)
 {
     std::string OutString ="";
     OutString +="Fie name \t" + Filename + "\n";
     OutString +="tile Y \t" + to_string(tileY) + "\n";
     OutString +="tile X \t" + to_string(tileY) + "\n";
     OutString +="pixel Count \t" + to_string(pixelCount) + "\n";
     OutString +="min \t" + to_string(minVal) + "\n";
     OutString +="max \t" + to_string(minVal) + "\n";
     OutString +="mean\t" + to_string(meanVal) + "\n";
     OutString +="stdVal \t" +to_string(stdVal) + "\n";
     for (int i = 0; i < 2048; i++)
     {
         OutString +=to_string(i*32)+"\t" + to_string(Hist[i]) + "\n";
     }
 }
 //-----------------------------------------------------------------------------------------------------------
 void IntensityStatistics::FromFile(string FileNameExt)
{
   Init();
   Mat Image;
   Image = imread(FileNameExt,CV_LOAD_IMAGE_ANYDEPTH);
   if(Image.empty())
       return;
   FileName = FileNameExt;
   int maxX = Image.cols;
   int maxY = Image.rows;
   int maxXY = maxX*maxY;
   unsigned short *wImage = (unsigned short *)Image.data;
   for(int i = 0; i < maxXY; i++)
   {
       unsigned short localVal = *wImage;
       int histIndex = localVal/32;
       Hist[histIndex]++;
       if(maxVal < localVal)
           maxVal = localVal;
       if(minVal < localVal)
           maxVal = localVal;
       wImage++;

   }
}
 //-----------------------------------------------------------------------------------------------------------

 void FeatureHistogram::PlotDirHistPlanar(int yScale, int scaleCoef, int barWidth)
 {
     const int topOffset = 30;
     const int bottomOffset = 30;
     const int scaleBarLenht = 5;
     const int leftOffset = 60;
     const int rightOffset = 20;
     const int digitWidth = 13;
     const int digitHeight = 10;

     int binCount = numberOfBins;

     int yScaleHeight = 100 * yScale;

     int plotYSize = yScaleHeight + topOffset + bottomOffset;
     int plotXSize = leftOffset + rightOffset + binCount *(1+barWidth);
     cv::Mat ImToShow = Mat(plotYSize,plotXSize,CV_8UC3,cv::Scalar(255,255,255));

     int nrOfCharacters = (int)featureName.size() ;
     putText(ImToShow,featureName,Point(plotXSize / 2 - nrOfCharacters * digitWidth / 2 ,
                                 topOffset / 2), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));

     line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),cv::Point(leftOffset - 2,topOffset),cv::Scalar(255.0,0.0,0.0,0.0));
     line(ImToShow,Point(leftOffset - 2,yScaleHeight + topOffset),Point(leftOffset+binCount*(1+barWidth),yScaleHeight + topOffset),Scalar(255.0,0.0,0.0,0.0));

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
     for(int x = 0; x <= binCount; x+= 40)
     {
         line(ImToShow,Point(leftOffset + x * (1 + barWidth) + barWidth /2, yScaleHeight + topOffset),
                       Point(leftOffset + x * (1 + barWidth) + barWidth /2,yScaleHeight + topOffset + scaleBarLenht),
                       Scalar(255.0,0.0,0.0,0.0));

         //std::ostringstream ss;
         //ss << std::fixed << std::setprecision(2) << (minValue + x * binRange);
         //std::string text = ss.str();
         string text = to_string(minValue + x * binRange);
         int nrOfdigits = (int)(text.size());
         putText(ImToShow,text,Point(leftOffset + x * (1 + barWidth)  - nrOfdigits * digitWidth / 2 ,
                                     yScaleHeight + topOffset + digitHeight * 2 + scaleBarLenht), FONT_HERSHEY_COMPLEX_SMALL, 1.0, Scalar(255.0,0.0,0.0,0.0));
     }

     Point orygin = Point(leftOffset, yScaleHeight + topOffset);
     for(int bin = 0; bin < binCount; bin++)
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
     imshow("Feature Hist",ImToShow);
 }

