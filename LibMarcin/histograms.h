#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include <opencv2/core/core.hpp>

class HistogramInteger
{
private:

    int64_t histSize;
    int64_t histMin;
    int64_t histMax;
    int64 mean;
    double meanD;
    int64_t min;
    int64_t max;
    int64_t count;
    int64_t binSize;
    int *Histogram;

    void Init();

    int checkMat16U(cv::Mat Im);
    int checkMat16U(cv::Mat Im, cv::Mat Mask);
    int checkMat32S(cv::Mat Im);

    void InitializeHistogram(int binS);

    void BasicStaistics16U(cv::Mat Im);
    void BasicStaistics16U(cv::Mat Im, cv::Mat Mask, int roiNr);
    void BasicStaistics32S(cv::Mat Im);

    void FindHistogram16U(cv::Mat Im);
    void FindHistogram16U(cv::Mat Im, cv::Mat Mask, int roiNr);
    void FindHistogram32S(cv::Mat Im);

public:

    HistogramInteger();
    ~HistogramInteger();

    void Release();

    int FromMat16U(cv::Mat, int binS = 1);
    int FromMat16U(cv::Mat Im, cv::Mat Mask, int roiNr, int binS = 1);
    int FromMat16ULimit(cv::Mat Im, int min, int max, int binS = 1);
    int FromMat16ULimit(cv::Mat Im, cv::Mat Mask, int roiNr, int min, int max, int binS = 1);
    int FromMat32S(cv::Mat, int binS = 1);

    std::string GetString();

    cv::Mat Plot(int yScale, int scaleCoef, int barWidth);
    cv::Mat PlotCummulative(int yScale);

    double GetStd();
    int64_t GetMin();
    int64_t GetMax();
    int64_t GetCount();
    int64_t GetMean();
    double GetMeanD();
    int getPosForCumulativeTh(double threshold);

    std::string StatisticStringOut(std::string separator = "\t");
};

class HistogramRGB
{
private:

    int64_t count;

    int64_t meanR;
    int64_t minR;
    int64_t maxR;
    int64_t maxPositionR;
    int64_t *HistogramR;

    int64_t meanG;
    int64_t minG;
    int64_t maxG;
    int64_t maxPositionG;
    int64_t *HistogramG;

    int64_t meanB;
    int64_t minB;
    int64_t maxB;
    int64_t maxPositionB;
    int64_t *HistogramB;


    void Init();

    int checkMat(cv::Mat Im);
    int checkMat(cv::Mat Im, cv::Mat Mask);


    void InitializeHistogram();

    void BasicStaistics(cv::Mat Im);
    void BasicStaistics(cv::Mat Im, cv::Mat Mask, int roiNr);

    void StaisticsFromHist();

    void FindHistogram(cv::Mat Im);
    void FindHistogram(cv::Mat Im, cv::Mat Mask, int roiNr);

    void FindMaxPos();
public:

    HistogramRGB();
    ~HistogramRGB();

    void Release();

    int FromMat(cv::Mat);
    int FromMat(cv::Mat Im, cv::Mat Mask, int roiNr);

    std::string GetString();

    cv::Mat Plot(int yScale, int scaleCoef, int barWidth, char colorPlane);
    cv::Mat PlotRGB(int yScale, int scaleCoef, int barWidth);

    int64_t GetCount();

    double GetStdB();
    int64_t GetMinB();
    int64_t GetMaxB();
    int64_t GetMeanB();
    int64_t GetMaxPositionB();

    double GetStdG();
    int64_t GetMinG();
    int64_t GetMaxG();
    int64_t GetMeanG();
    int64_t GetMaxPositionG();

    double GetStdR();
    int64_t GetMinR();
    int64_t GetMaxR();
    int64_t GetMeanR();
    int64_t GetMaxPositionR();

    void smoothHistogram();
};



std::string StatisticStringHeader(std::string separator = "\t" );

#endif // HISTOGRAMS_H
