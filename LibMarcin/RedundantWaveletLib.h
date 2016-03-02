#ifndef RedundantWaveletLib
#define RedundantWaveletLib
//--------------------------------------------------------------------------------------------
using namespace cv;
using namespace std;

//-----------------------------------------------------------------------------------------------------------------
Mat RedundantWaveletLLFilter(int scale);
Mat RedundantWaveletHLFilter(int scale);
Mat RedundantWaveletLHFilter(int scale);
Mat RedundantWaveletHHFilter(int scale);

unsigned short RoiPositions(Mat ImRoi, int *minPosX, int *maxPosX, int *minPosY, int *maxPosY);

float MeanEnergyCalculaton(Mat ImIn,Mat Roi,unsigned short roiNr);

Mat MeanEnergyImage(Mat ImIn, Mat Roi, unsigned short roiNr);
#endif
