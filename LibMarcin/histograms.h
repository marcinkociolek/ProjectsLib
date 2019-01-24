#ifndef HISTOGRAMS_H
#define HISTOGRAMS_H

#include <opencv2/core/core.hpp>

class HistogramInteger
{

public:
    int histSize;
    int histMin;
    int histMax;
    int *Histogram;
    HistogramInteger();
    ~HistogramInteger();
    void Release();
    int FromMat(cv::Mat);
    std::string GerString();
    cv::Mat Plot(int yScale, int scaleCoef, int barWidth);
};

#endif // HISTOGRAMS_H
