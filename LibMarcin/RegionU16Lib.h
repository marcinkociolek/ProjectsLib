#ifndef RegionU16Lib
#define RegionU16Lib

#include <opencv2/core/core.hpp>

using namespace cv;



Mat RemovingTinyReg9(Mat ImReg);
void FillBorderWithValue(Mat ImReg, float value);
void OneRegionFill5Fast1(Mat ImR,  unsigned short fillReg);
void FillHoles(Mat ImR);
void DeleteRegionFromImage(Mat ImR, unsigned short regToRemove);
unsigned short DivideSeparateRegions(Mat ImReg, unsigned int minRegSize);
void RegionExchange(unsigned short *ImReg, int stop,
                    unsigned short rI, unsigned  short rO);

void DeleteRegTouchingBorder(Mat ImReg);

void RegionDilation5(Mat ImR);
void RegionDilation9(Mat ImR);
void RegionDilation13(Mat ImR);

void RegionErosion5(Mat ImR);
void RegionErosion9(Mat ImR);
void RegionErosion13(Mat ImR);

//Mat GetContour5(Mat ImR);


//-----------------------------------------------------------------------------
int CenterOfMas(Mat ImReg, int *centerX, int *centerY);
int CenterOfMas(Mat ImReg, int *centerX, int *centerY, unsigned short reg);

int PartOfRegionAtTheAngle(Mat ImReg, Mat ImRegOut,  int centerX, int centerY,
                           int directionDeg, int angleDeg,
                           unsigned short inRegNr, unsigned short outRegNr);

//void ShowRegionOnImage16(Mat ImReg, Mat ImRGB);

cv::Mat CreateRoi16(int Shape, int maxX, int maxY);

cv::Mat Threshold16(cv::Mat ImIn, unsigned short threshold);
void Threshold16(cv::Mat ImIn, cv::Mat Mask, unsigned short threshold);

cv::Mat BuildKernel(int shape);
void DilationCV(cv::Mat Mask, int shape);
void ErosionCV(cv::Mat Mask, int shape);

cv::Mat MaskOutsideMatOut(cv::Mat Im, cv::Mat Mask);
int MaskOutside(cv::Mat Im, cv::Mat Mask);

#endif // GRADIENT

