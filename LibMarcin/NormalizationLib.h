#ifndef NormalizationLib
#define NormalizationLib
//--------------------------------------------------------------------------------------------
//#include <stdio.h>
//using namespace cv;
//using namespace std;
//--------------------------------------------------------------------------------------------
void NormParamsMinMax(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParamsMeanP3Std(cv::Mat Im, double *maxNorm, double *minNorm);
void NormParams1to99perc(cv::Mat ImIn, double *maxNorm, double *minNorm);

void NormParamsMinMax(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, float *maxNorm, float *minNorm);
void NormParamsMeanP3Std(cv::Mat Im, cv::Mat Roi, unsigned short roiNr, float *maxNorm, float *minNorm);
void NormParams1to99perc(cv::Mat ImIn, cv::Mat Roi, unsigned short roiNr, float *maxNorm, float *minNorm);

//--------------------------------------------------------------------------------------------
#endif
