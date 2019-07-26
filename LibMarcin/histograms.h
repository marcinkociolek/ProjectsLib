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





#endif // HISTOGRAMS_H
