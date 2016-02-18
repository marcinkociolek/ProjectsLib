#ifndef NormalizationLib
#define NormalizationLib
//--------------------------------------------------------------------------------------------
//#include <stdio.h>
using namespace cv;
using namespace std;
//--------------------------------------------------------------------------------------------
void NormParamsMinMax(Mat Im, float *maxNorm, float *minNorm);
void NormParamsMeanP3Std(Mat Im, float *maxNorm, float *minNorm);
void NormParams1to99perc(Mat ImIn, float *maxNorm, float *minNorm);

//--------------------------------------------------------------------------------------------
#endif