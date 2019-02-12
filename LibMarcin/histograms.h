#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include <opencv2/core/core.hpp>

class HistogramInteger
{

public:
    int histSize;
    int histMin;
    int histMax;
    int histMean;
    int *Histogram;
    HistogramInteger();
    ~HistogramInteger();
    void Release();
    int FromMat16U(cv::Mat);
    int FromMat32S(cv::Mat);
    std::string GetString();
    cv::Mat Plot(int yScale, int scaleCoef, int barWidth);
};





#endif // HISTOGRAMS_H
