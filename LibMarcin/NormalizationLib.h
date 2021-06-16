#ifndef NormalizationLib
#define NormalizationLib
//--------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
//#include <stdio.h>
//--------------------------------------------------------------------------------------------
void NormParamsMinMax(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParamsMeanP3Std(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParams1to99perc(cv::Mat ImIn, double *maxNorm, double *minNorm);

void NormParamsMinMax(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
void NormParamsMeanP3Std(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
void NormParams1to99perc(cv::Mat ImIn, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
//--------------------------------------------------------------------------------------------
void NormParamsMinMax16U(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParamsMeanP3Std16U(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParams1to99perc16U(cv::Mat ImIn, double *maxNorm, double *minNorm);

void NormParamsMinMax16U(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
void NormParamsMeanP3Std16U(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
void NormParams1to99perc16U(cv::Mat ImIn, cv::Mat Roi, unsigned short roiNr, double *maxNorm, double *minNorm);
//--------------------------------------------------------------------------------------------
#endif
