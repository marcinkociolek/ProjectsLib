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
    boost::filesystem::path ImFolderName;
    int tileShape;
    int tileSize;
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

class FeatureHistogram
{
public:
    std::string featureName;
    int numberOfBins;
    int numberOfElements;

    int *Histogram;

    double minValue;
    double maxValue;
    double binRange;

    int maxHistVal;
    int maxHistPosition;

    void GetHitogram(FileParams Params, int featureNr, int numberOfBinsIn = 40)
    {
        featureName.clear();
        numberOfBins = 0;
        delete[] Histogram;
        Histogram = 0;

        featureName = Params.NamesVector[featureNr+2];
        if(Params.ParamsVect.empty())
        {
            numberOfBins = 0;
            return;
        }
        if(Params.ParamsVect[0].Params.empty())
        {
            numberOfBins = 0;
            return;
        }
        if(Params.ParamsVect[0].paramsCount < (featureNr + 1))
        {
            numberOfBins = 0;
            return;
        }

        numberOfBins = numberOfBinsIn;
        Histogram = new int[numberOfBins];
        for(int i = 0; i < numberOfBins; i++)
        {
            Histogram[i] = 0;
        }

        minValue = Params.ParamsVect[0].Params[featureNr];
        maxValue = Params.ParamsVect[0].Params[featureNr];
        for(int i = 1; i < Params.ValueCount; i++)
        {
            if(Params.ParamsVect[0].paramsCount < (featureNr + 1))
                continue;
            if(minValue > Params.ParamsVect[i].Params[featureNr])
                minValue = Params.ParamsVect[i].Params[featureNr];
            if(maxValue < Params.ParamsVect[i].Params[featureNr])
                maxValue = Params.ParamsVect[i].Params[featureNr];
        }

        double histogramRange = maxValue - minValue;
        binRange = (histogramRange)/(double)numberOfBins;

        numberOfElements = 0;

        for(int i = 0; i < Params.ValueCount; i++)
        {
            if(Params.ParamsVect[0].paramsCount < (featureNr + 1))
                continue;

            int binVal = (int)floor((Params.ParamsVect[i].Params[featureNr] - minValue)/histogramRange*numberOfBins);
            if(binVal >= numberOfBins)
                continue;
            numberOfElements++;
            Histogram[binVal]++;
        }
     }

    void PlotDirHistPlanar(int yScale, int scaleCoef, int barWidth = 3);

    FeatureHistogram()
    {
        featureName.clear();
        numberOfBins = 0;
        delete[] Histogram;
        Histogram = 0;
    }

    ~FeatureHistogram()
    {
        featureName.clear();
        numberOfBins = 0;
        delete[] Histogram;
        Histogram = 0;
    }
};

#endif // TILEPARAMS_H
