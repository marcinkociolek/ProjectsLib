#include "tileparams.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

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
     NamesVector.empty();
     ParamsVect.empty();
 }

 FileParams::~FileParams()
 {
     ImFileName.empty();
     ImFolderName.empty();
     tileShape = -1;
     tileSize = -1;
     ValueCount = 0;
     NamesVector.empty();
     ParamsVect.empty();
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
