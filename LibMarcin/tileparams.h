#ifndef TILEPARAMS_H
#define TILEPARAMS_H

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <opencv2/core.hpp>
#include <boost/regex.hpp>

class TileParams
{
public:
    int tileY;
    int tileX;
    int paramsCount;
    std::vector<float>Params;

    TileParams();
    ~TileParams();
    void FromString(std::string);
};


class FileParams
{
public:
    boost::filesystem::path ImFileName;
    int tileShape;
    int maxTileX;
    int maxTileY;
    int shiftTileX;
    int shiftTileY;
    int offsetTileX;
    int offsetTileY;
    int ValueCount;
    std::vector<std::string> NamesVector;
    std::vector<TileParams> ParamsVect;

    FileParams();
    ~FileParams();

};

class IntensityStatistics
{
public:
    int tileY;
    int tileX;
    int pixelCount;
    int *Hist;
    int minVal;
    int maxVal;
    int modeVal;
    double meanVal;
    double stdVal;
    std::string FileName;

    IntensityStatistics()
    {
        Init();
    }

    void Init()
    {
        tileY = -1;
        tileX = -1;
        pixelCount = 0;
        Hist = new int[2048];
        for(int i = 0; i <2048 ;i++)
            Hist[i] = 0;
        minVal = 65536;
        maxVal = 0;
        modeVal = 0;
        meanVal = 0;
        stdVal = 0;
        FileName.empty();
    }
    ~IntensityStatistics()
    {
        delete[] Hist;
        Hist = 0;
        FileName.empty();
    }
    void SaveToFile(std::string FileMameOut);
    void FromFile(std::string FileNameIn);
};

#endif // TILEPARAMS_H
