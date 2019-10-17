#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include <opencv2/core/core.hpp>

class HistogramInteger
{
private:

    int64_t histSize;
    int64_t histMin;
    int64_t histMax;
    int64_t mean;
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
    int FromMat16ULimit(cv::Mat Im, cv::Mat Mask, int roiNr, int min, int max, int binS = 1);
    int FromMat32S(cv::Mat, int binS = 1);

    std::string GetString();

    cv::Mat Plot(int yScale, int scaleCoef, int barWidth);
};

class HistogramRGB
{
private:

    int64_t count;

    int64_t meanR;
    int64_t minR;
    int64_t maxR;

    int *HistogramR;

    int64_t meanG;
    int64_t minG;
    int64_t maxG;
    int *HistogramG;

    int64_t meanB;
    int64_t minB;
    int64_t maxB;
    int *HistogramB;


    void Init();

    int checkMat(cv::Mat Im);
    int checkMat(cv::Mat Im, cv::Mat Mask);


    void InitializeHistogram();

    void BasicStaistics(cv::Mat Im);
    void BasicStaistics(cv::Mat Im, cv::Mat Mask, int roiNr);

    void FindHistogram(cv::Mat Im);
    void FindHistogram(cv::Mat Im, cv::Mat Mask, int roiNr);


public:

    HistogramRGB();
    ~HistogramRGB();

    void Release();

    int FromMat(cv::Mat);
    int FromMat(cv::Mat Im, cv::Mat Mask, int roiNr);

    std::string GetString();

    cv::Mat Plot(int yScale, int scaleCoef, int barWidth, char colorPlane);
    cv::Mat PlotRGB(int yScale, int scaleCoef, int barWidth);
};



#endif // HISTOGRAMS_H
