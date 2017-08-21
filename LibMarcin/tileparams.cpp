#include "tileparams.h"
#include <iostream>
#include <sstream>
#include <vector>

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

}


 FileParams::FileParams()
 {
     ImFileName = "";
     tileShape = -1;
     maxTileX = -1;
     maxTileY = -1;
     shiftTileX = -1;
     shiftTileY = -1;
     offsetTileX = -1;
     offsetTileY = -1;
     ValueCount = 0;
     NamesVector.empty();
     ParamsVect.empty();
 }

 FileParams::~FileParams()
 {
     ImFileName.empty();
     tileShape = -1;
     maxTileX = -1;
     maxTileY = -1;
     shiftTileX = -1;
     shiftTileY = -1;
     offsetTileX = -1;
     offsetTileY = -1;
     ValueCount = 0;
     NamesVector.empty();
     ParamsVect.empty();
 }
