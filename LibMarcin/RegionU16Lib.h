#ifndef RegionU16Lib
#define RegionU16Lib

#include <opencv2/core/core.hpp>

cv::Mat RemovingTinyReg9(cv::Mat ImReg);
void FillBorderWithValue(cv::Mat ImReg, float value);
void OneRegionFill5Fast1(cv::Mat ImR,  unsigned short fillReg);
void FillHoles(cv::Mat ImR, unsigned short region = 1);
void DeleteRegionFromImage(cv::Mat ImR, unsigned short regToRemove);
unsigned short DivideSeparateRegions(cv::Mat ImReg, unsigned int minRegSize);
void RegionExchange(unsigned short *ImReg, int stop,
                    unsigned short rI, unsigned  short rO);

void DeleteRegTouchingBorder(cv::Mat ImReg);

void RegionDilation5(cv::Mat ImR);
void RegionDilation9(cv::Mat ImR);
void RegionDilation13(cv::Mat ImR);

void RegionErosion5(cv::Mat ImR);
void RegionErosion9(cv::Mat ImR);
void RegionErosion13(cv::Mat ImR);

//Mat GetContour5(Mat ImR);


//-----------------------------------------------------------------------------
int CenterOfMas(cv::Mat ImReg, int *centerX, int *centerY);
int CenterOfMas(cv::Mat ImReg, int *centerX, int *centerY, unsigned short reg);

int PartOfRegionAtTheAngle(cv::Mat ImReg, cv::Mat ImRegOut,  int centerX, int centerY,
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

int MaskInside(cv::Mat Im, cv::Mat Mask);

//----------------------------------------------------------------------------------------------------------------------
int MaskMaskInv(cv::Mat Mask, cv::Mat Mask2);


#endif // GRADIENT

