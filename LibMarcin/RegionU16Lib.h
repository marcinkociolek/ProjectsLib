#ifndef RegionU16Lib
#define RegionU16Lib

#include <opencv2/core/core.hpp>
class RegionParams
{
public:
    int area;
    int maxX;
    int maxY;
    int minX;
    int minY;
    int massCenterX;
    int massCenterY;
    int sizeX;
    int sizeY;
    int temp;
    bool valid;

    void Init()
    {
        area = 0;
        maxX = 0;
        maxY = 0;
        minX = 100000;
        minY = 100000;
        massCenterX = 0;
        massCenterY = 0;
        sizeX = -1;
        sizeY = -1;
        temp = 0;
        valid = true;
    }

    RegionParams()
    {
        Init();
    }
};

class MultiRegionsParams
{
public:
    MultiRegionsParams()
    {
        Init();
    }
    MultiRegionsParams(cv::Mat Mask)
    {
        Init();
        GetFromMat(Mask);
    }
    ~MultiRegionsParams()
    {
        if((RegionsParams != nullptr) && (count > 0) )
            delete [] RegionsParams;
    }
    void GetFromMat(cv::Mat Mask)
    {
        if(Mask.empty())
            return;
        if(Mask.type() != CV_16U)
            return;
        int maxRegionNr = 0;

        int maxX = Mask.cols;
        int maxY = Mask.rows;
        int maxXY = maxX * maxY;

        uint16_t *wMask;
        wMask = (uint16_t *)Mask.data;
        for(int i = 0; i < maxXY; i++)
        {
            if(maxRegionNr < *wMask)
                maxRegionNr = *wMask;
            wMask++;
        }
        count = maxRegionNr;
        RegionsParams = new RegionParams[count + 1];
        for(int k = 0; k <= count; k++)
        {
            RegionsParams[k].Init();
        }
        wMask = (uint16_t *)Mask.data;

        for(int y = 0; y < maxY; y++)
        {
            for(int x = 0; x < maxX; x++)
            {
                int regionIndex = *wMask;
                RegionsParams[regionIndex].area++;
                if(RegionsParams[regionIndex].maxX < x)
                    RegionsParams[regionIndex].maxX = x;
                if(RegionsParams[regionIndex].maxY < y)
                    RegionsParams[regionIndex].maxY = y;
                if(RegionsParams[regionIndex].minX > x)
                    RegionsParams[regionIndex].minX = x;
                if(RegionsParams[regionIndex].minY > y)
                    RegionsParams[regionIndex].minY = y;
                RegionsParams[regionIndex].massCenterX += x;
                RegionsParams[regionIndex].massCenterY += y;

                wMask++;
            }
        }

        for(int k = 0; k <= count; k++)
        {
            if(RegionsParams[k].area)
            {
                RegionsParams[k].sizeX = RegionsParams[k].maxX - RegionsParams[k].minX + 1;
                RegionsParams[k].sizeY = RegionsParams[k].maxY - RegionsParams[k].minY + 1;
                RegionsParams[k].massCenterX /= RegionsParams[k].area;
                RegionsParams[k].massCenterY /= RegionsParams[k].area;
            }
        }
    }

    RegionParams GetRegionParams(int regionNr)
    {
        if (regionNr > count || regionNr < 0)
            return RegionParams();
        else
            return  RegionsParams[regionNr];
    }

    int GetCountOfNonZeroArea()
    {
        int out = 0;
        for(int k = 1; k <= count; k++)
        {
            if(RegionsParams[k].area)
                out++;
        }
        return out;
    }

    int GetCountOfNonZeroAreaValid()
    {
        int out = 0;
        for(int k = 1; k <= count; k++)
        {
            if(RegionsParams[k].area && RegionsParams[k].valid)
                out++;
        }
        return out;
    }

    int GetCountOfNonZeroAreaNonValid()
    {
        int out = 0;
        for(int k = 1; k <= count; k++)
        {
            if(RegionsParams[k].area && (RegionsParams[k].valid == false))
                out++;
        }
        return out;
    }

    bool SetValid(int regionNr, bool valid)
    {
        if(regionNr > count)
        {
            return false;
        }
        RegionsParams[regionNr].valid = valid;
        return true;
    }

private:
    RegionParams * RegionsParams;
    int count;

    void Init()
    {
        RegionsParams = nullptr;
        count = 0;
    }
};



cv::Mat RemovingTinyReg9(cv::Mat ImReg);
void FillBorderWithValue(cv::Mat ImReg, float value);
void OneRegionFill5Fast1(cv::Mat ImR,  unsigned short fillReg);
void FillHoles(cv::Mat ImR, unsigned short region = 1);
void DeleteRegionFromImage(cv::Mat ImR, unsigned short regToRemove);
void KeepOneRegion(cv::Mat ImR, unsigned short regToKeep);
unsigned short DivideSeparateRegions(cv::Mat ImReg, unsigned int minRegSize);
void RegionExchange(unsigned short *ImReg, int stop,
                    unsigned short rI, unsigned  short rO);

void DeleteRegTouchingBorder(cv::Mat ImReg);

void RegionDilation5(cv::Mat ImR);
void RegionDilation9(cv::Mat ImR);
void RegionDilation13(cv::Mat ImR);

void RegionErosion5(cv::Mat ImR);
void RegionErosion5ZeroPad(cv::Mat ImR);
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
cv::Mat BuildRoundedKernell(int radius);
void DilationCircleCV(cv::Mat Mask, int radius);
void ErosionCircleCV(cv::Mat Mask, int radius);

cv::Mat MaskOutsideMatOut(cv::Mat Im, cv::Mat Mask);
int MaskOutside(cv::Mat Im, cv::Mat Mask);

int MaskInside(cv::Mat Im, cv::Mat Mask);
//----------------------------------------------------------------------------------------------------------------------
int MaskMaskInv(cv::Mat Mask, cv::Mat Mask2);
cv::Mat MaskInv(cv::Mat Mask);
//----------------------------------------------------------------------------------------------------------------------
cv::Mat Combine2Regions(cv::Mat Mask1, cv::Mat Mask2);
cv::Mat Combine2RegionsTo8Bit(cv::Mat Mask1, cv::Mat Mask2);
cv::Mat Combine3Regions(cv::Mat Mask1, cv::Mat Mask2, cv::Mat Mask3);
cv::Mat Combine3RegionsTo8Bit(cv::Mat Mask1, cv::Mat Mask2, cv::Mat Mask3);
//----------------------------------------------------------------------------------------------------------------------
cv::Point  GetRegionCentroid(cv::Mat Mask, unsigned short regionNumber);

//----------------------------------------------------------------------------------------------------------------------
int RemoveOverlapingRegions(cv::Mat MaskToModify, cv::Mat Mask);


#endif // GRADIENT

