#ifndef HaralickLib
#define HaralickLib
//--------------------------------------------------------------------------------------------
//#include <stdio.h>
using namespace cv;
using namespace std;
//--------------------------------------------------------------------------------------------
//Mat KernelPrepare(int offset, float angle);
Mat KernelPrepare(int offset, float angle, int interpolation = INTER_AREA);
Mat COMCardone(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm);
Mat COMCardone2(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm);
Mat COMCardone3(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm, int interpolation = INTER_AREA);
Mat COMCardone4(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm, int interpolation = INTER_AREA);

Mat COMCardoneRoi(Mat ImInFloat, Mat Roi, int ofset, float angle, int binCount, float maxNorm, float minNorm, int interpolation, unsigned short roiNr);

Mat COMCardone5(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm);
Mat COMCardoneRoi5(Mat ImInFloat, Mat Roi, int ofset, float angle, int binCount, float maxNorm, float minNorm, unsigned short roiNr);


Mat COMHorizontalRoi(Mat ImInFloat, Mat Roi, int ofset, int binCount, float maxNorm, float minNorm, unsigned short roiNr);

Mat COMLatice4(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm, int interpolation);

void COMParams(Mat COM, float *contrastOut, float *energyOut, float *homogenityOut, float *correlationOut);

float COMCorrelation(Mat COM);
//--------------------------------------------------------------------------------------------

Mat COMCardoneLatice(Mat ImInFloat, int ofset, float angle, int binCount, float maxNorm, float minNorm);
//--------------------------------------------------------------------------------------------
int FindBestAngleMin(float *Feature, int size);
int FindBestAngleMax(float *Feature, int size);

float BestAngleQualityScoreMin(float *Feature, int size, int bestAngleIndex);
float BestAngleQualityScoreMax(float *Feature, int size, int bestAngleIndex);
float BestAngleQualityScore(float *Feature, int size, int bestAngleIndex);

//---------------------------------------------------------------------------------------------
Mat COMStd(Mat ImIn, Mat ROI, int ofset, int angleNr, unsigned short roiNr, bool symetricCom, int binCount, float maxNorm, float minNorm);

#endif
