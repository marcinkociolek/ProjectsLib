#include "RegionU16Lib.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

Mat RemovingTinyReg9(Mat ImR)
{
// renewed version sweeps whole image
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    Mat ImRTemp = Mat::zeros(maxY,maxX,CV_16U);

    unsigned short *wImRTemp = (unsigned short*)ImRTemp.data;

    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX - 1;
    unsigned short *wImR2 = wImR0 - maxX;
    unsigned short *wImR3 = wImR0 - maxX + 1;
    unsigned short *wImR4 = wImR0 - 1;
    unsigned short *wImR5 = wImR0 + 1;
    unsigned short *wImR6 = wImR0 + maxX - 1;
    unsigned short *wImR7 = wImR0 + maxX;
    unsigned short *wImR8 = wImR0 + maxX + 1;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned short sum = 0;
        if (y > 0 && x > 0)
        {
            sum += *wImR1;
        }
        if (y > 0)
        {
            sum += *wImR2;
        }
        if (y > 0 && x < maxXa)
        {
            sum += *wImR3;
        }
        if (x > 0)
        {
            sum += *wImR4;
        }
        if (x < maxXa)
        {
            sum += *wImR5;
        }
        if (y < maxYa && x > 0)
        {
            sum += *wImR6;
        }
        if (y < maxYa)
        {
            sum += *wImR7;
        }
        if (y < maxYa && x < maxXa)
        {
            sum += *wImR8;
        }

        if(sum)
            *wImRTemp = *wImR0;
        else
            *wImRTemp = 0;

        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
    }
    return ImRTemp;
}
//---------------------------------------------------------------------------
void FillBorderWithValue(Mat ImReg, float value)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    int maxXY = maxX * maxY;
    unsigned short *wImReg; // moving pointer
    // first row
    wImReg = (unsigned short*)ImReg.data;
    for(int i = 0; i < maxX; i++)
    {
        if(!*wImReg)
            *wImReg = value;
        wImReg++;
    }
    // last row
    wImReg = (unsigned short*)ImReg.data + maxXY - maxX;
    for(int i = 0; i < maxX; i++)
    {
        if(!*wImReg)
            *wImReg = value;
        wImReg++;
    }
    // first column
    wImReg = (unsigned short*)ImReg.data;
    for(int i = 0; i < maxY; i++)
    {
        if(!*wImReg)
            *wImReg = value;
        wImReg += maxX;
    }
    // last row
    wImReg = (unsigned short*)ImReg.data + maxX-1;
    for(int i = 0; i < maxY; i++)
    {
        if(!*wImReg)
            *wImReg = value;
        wImReg += maxX;
    }
}
//------------------------------------------------------------------------------
void OneRegionFill5Fast1(Mat ImR,  unsigned short fillReg)
{
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;

    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    bool wasAction = 1;

    while(1)
    {
        wasAction = 0;
        unsigned short *wImR0 = (unsigned short*)ImR.data;
        unsigned short *wImR1 = wImR0 - maxX;
        unsigned short *wImR2 = wImR0 - 1;
        unsigned short *wImR3 = wImR0 + 1;
        unsigned short *wImR4 = wImR0 + maxX;


        for (int i = 0; i < maxXY; i++)
        {
            int x = i % maxX;
            int y = i / maxX;

            if (x > 0 && x < maxXa && y > 0 && y < maxYa)
            {
                if(*wImR0 == 0 &&
                   (*wImR1 == fillReg || *wImR2 == fillReg ||
                    *wImR3 == fillReg || *wImR4 == fillReg ))
                {
                    *wImR0 = fillReg;
                    wasAction = 1;
                }
            }
            wImR0++;
            wImR1++;
            wImR2++;
            wImR3++;
            wImR4++;
        }
        if(!wasAction)
            return;

        wasAction = 0;
        wImR0 = (unsigned short*)ImR.data + maxXY;
        wImR1 = wImR0 - maxX;
        wImR2 = wImR0 - 1;
        wImR3 = wImR0 + 1;
        wImR4 = wImR0 + maxX;

        for (int i = maxXY; i > 0; i--)
        {
            int x = i % maxX;
            int y = i / maxX;

            if (x > 0 && x < maxXa && y > 0 && y < maxYa)
            {
                if(*wImR0 == 0 &&
                   (*wImR1 == fillReg || *wImR2 == fillReg ||
                    *wImR3 == fillReg || *wImR4 == fillReg ))
                {
                    *wImR0 = fillReg;
                    wasAction = 1;
                }
            }
            wImR0--;
            wImR1--;
            wImR2--;
            wImR3--;
            wImR4--;
        }
        if(!wasAction)
            return;
    }
}
//------------------------------------------------------------------------------
void FillHoles(Mat ImR, unsigned short region)
{
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    unsigned short *wImR = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        if(*wImR == 0)
            *wImR = region;
        wImR++;
    }
}
//---------------------------------------------------------------------------
void DeleteRegionFromImage(Mat ImR, unsigned short regToRemove)
{
    if(!regToRemove)
        return;
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    unsigned short *wImR = (unsigned short*)ImR.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(*wImR == regToRemove)
            *wImR = 0;
        wImR++;
    }
}
//---------------------------------------------------------------------------
unsigned short DivideSeparateRegions(Mat InReg, unsigned int minRegSize)
// fonction returns number of new segments
{
    int maxX = InReg.cols;
    int maxY = InReg.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    unsigned short *OutReg = new unsigned short[maxXY];


    // moving pointers
    unsigned short *wInReg = (unsigned short*)InReg.data;

    unsigned short *wInRegN1 = wInReg - 1; 		//y  ,x-1
    unsigned short *wInRegN2 = wInReg - maxX - 1; 	//y-1,x+1
    unsigned short *wInRegN3 = wInReg - maxX; 	//y-1,x
    unsigned short *wInRegN4 = wInReg - maxX + 1; 	//y-1,x-1

    unsigned short *wOutReg = OutReg;

    unsigned short *wOutRegN1 = OutReg - 1; 	//y  ,x-1
    unsigned short *wOutRegN2 = OutReg - maxX - 1; 	//y-1,x+1
    unsigned short *wOutRegN3 = OutReg - maxX; 	//y-1,x
    unsigned short *wOutRegN4 = OutReg - maxX + 1; 	//y-1,x-1

    unsigned short newReg = 1;

    int maxRegNr = 0xFFFC;
    unsigned short *Exchange = new unsigned short[maxRegNr];
    unsigned int *RegionSizes = new unsigned int[maxRegNr];

    unsigned short *wExchange = Exchange;
    unsigned int *wRegionSizes = RegionSizes;

    for (int i = 0; i < maxRegNr; i++)
    {
        *wExchange = i;
        *wRegionSizes = 0;
        wExchange++;
        wRegionSizes++;
    }

    unsigned short SameRegion[4];
    int iSameRegion;

    int licznik = 0;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;
        if(*wInReg > 0 && *wInReg < 0xFFFD)
        {
            iSameRegion = -1;

            SameRegion[0] = 0xFFFF;
            SameRegion[1] = 0xFFFF;
            SameRegion[2] = 0xFFFF;
            SameRegion[3] = 0xFFFF;

            if (x > 0 && *wInReg == *wInRegN1)
            {
                iSameRegion++;
                SameRegion[iSameRegion] = *wOutRegN1;
            }
            if (y > 0 && x > 0 && *wInReg == *wInRegN2)
            {
                iSameRegion++;
                SameRegion[iSameRegion] = *wOutRegN2;
            }
            if (y > 0 && *wInReg == *wInRegN3)
            {
                iSameRegion++;
                SameRegion[iSameRegion] = *wOutRegN3;
            }
            if (y > 0 && x < maxXa &&*wInReg == *wInRegN4)
            {
                iSameRegion++;
                SameRegion[iSameRegion] = *wOutRegN4;
            }
            // there is no same neughbours. Create new region
            if (iSameRegion == -1)
            {
               *wOutReg = newReg;
               newReg++;
            }
            else
            {
                // looking for the smalest region
                unsigned short minSameRegion = SameRegion[0];
                for (int k = 1; k <= iSameRegion; k++)
                    if (minSameRegion > SameRegion[k])
                        minSameRegion = SameRegion[k];

                *wOutReg = minSameRegion;

                //Updating conversion table
                for (int k = 0; k <= iSameRegion; k++)
                    if(SameRegion[k] != minSameRegion)
                    {
                        RegionExchange(OutReg, i - 1,SameRegion[k], minSameRegion);
                        licznik++;
                    }
            }
        }
        else
            *wOutReg = *wInReg;

        //updating pointers
        wInReg++;

        wInRegN1++;
        wInRegN2++;
        wInRegN3++;
        wInRegN4++;

        wOutReg++;

        wOutRegN1++;
        wOutRegN2++;
        wOutRegN3++;
        wOutRegN4++;
    }

    wInReg = (unsigned short*)InReg.data;
    wOutReg = OutReg;
    for (int i = 0; i < maxXY; i++)
    {

        *wInReg = *wOutReg;
        RegionSizes[*wInReg]++;
        wInReg++;
        wOutReg++;
    }
    //--------------------------------------------------------------------------
    // usuwanie ma?ych obszarów zmiana numeracji
    unsigned short newRegNR = 1;
    for(unsigned short k = 1; k <= newReg; k++)
    {
        if (RegionSizes[k] <=   minRegSize)
        {
            Exchange[k] = 0;
        }
        else
        {
            Exchange[k] = newRegNR;
            newRegNR++;
        }
    }
    wInReg = (unsigned short*)InReg.data;
    //unsigned short oldRegNr;
    for (int i = 0; i < maxXY; i++)
    {
        if(*wInReg < 0xFFFD)
            *wInReg = Exchange[*wInReg];
        wInReg++;
    }
    delete[] Exchange;
    delete[] RegionSizes;
    delete[] OutReg;

    return (newRegNR - 1);
}
//------------------------------------------------------------------------------
void RegionExchange(unsigned short *ImReg, int stop,
                    unsigned short rI, unsigned  short rO)
{
    unsigned short *wImReg = ImReg;
    for (int i = 0; i <= stop; i++)
    {
        if(*wImReg == rI)
        {
            *wImReg = rO;
        }
        wImReg++;
    }
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void DeleteRegTouchingBorder(Mat ImReg)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    //int maxXY = maxX * maxY;

//    int maxXa = maxX - 1;
//    unsigned short *OutReg = new unsigned short[maxXY];

    bool RegToRemove[0xFFFF];
    bool *wRegToRemove = RegToRemove;
    for(int i = 0;i <= 0xFFFF; i++)
    {
        *wRegToRemove = 0;
        wRegToRemove++ ;
    }
    // first row
    unsigned short *wImReg;
    wImReg = (unsigned short*)ImReg.data;
    for(int i = 0;i < maxX; i++)
    {
        if(*wImReg)
            RegToRemove[*wImReg] = 1;
        wImReg++;
    }
    //last row
    wImReg = (unsigned short*)ImReg.data + maxX * (maxY - 1);
    for(int i = 0;i < maxX; i++)
    {
        if(*wImReg)
            RegToRemove[*wImReg] = 1;
        wImReg++;
    }

    wImReg = (unsigned short*)ImReg.data;
    for(int i = 0;i < maxY; i++)
    {
        if(*wImReg)
            RegToRemove[*wImReg] = 1;
        wImReg += maxX;
    }
    wImReg = (unsigned short*)ImReg.data + maxX - 1;
    for(int i = 0;i < maxY-1; i++)
    {
        if(*wImReg)
            RegToRemove[*wImReg] = 1;
        wImReg += maxX;
    }

    unsigned short RegToRemoveList[65535];
    int iRegToRemoveList = -1;
    wRegToRemove = RegToRemove + 1;
    for(int i = 1;i <= 0xFFFF; i++)
    {
        if(*wRegToRemove)
        {
            iRegToRemoveList++;
            RegToRemoveList[iRegToRemoveList] = i;
        }
        wRegToRemove++;
    }
    if(iRegToRemoveList == -1)
        return;
    for(int i = 0; i <= iRegToRemoveList; i++)
    {
        DeleteRegionFromImage(ImReg, RegToRemoveList[i]);
    }
    DivideSeparateRegions(ImReg, 0);
    return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void RegionDilation5(Mat ImR)
{
// renewed version dilates whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX;
    unsigned short *wImR2 = wImR0 - 1;
    unsigned short *wImR3 = wImR0 + 1;
    unsigned short *wImR4 = wImR0 + maxX;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int sum = (unsigned int)*wImR0;
        if (y > 0)
        {
            sum += (unsigned int)*wImR1;
        }
        if (x > 0)
        {
            sum += (unsigned int)*wImR2;
        }
        if (x < maxXa)
        {
            sum += (unsigned int)*wImR3;
        }
        if (y < maxYa)
        {
            sum += (unsigned int)*wImR4;
        }
        if(sum)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;

        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
void RegionDilation9(Mat ImR)
{
// renewed version dilates whole image
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX - 1;
    unsigned short *wImR2 = wImR0 - maxX;
    unsigned short *wImR3 = wImR0 - maxX + 1;
    unsigned short *wImR4 = wImR0 - 1;
    unsigned short *wImR5 = wImR0 + 1;
    unsigned short *wImR6 = wImR0 + maxX - 1;
    unsigned short *wImR7 = wImR0 + maxX;
    unsigned short *wImR8 = wImR0 + maxX + 1;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int sum = (unsigned int)*wImR0;
        if (y > 0 && x > 0)
        {
            sum += (unsigned int)*wImR1;
        }
        if (y > 0)
        {
            sum += (unsigned int)*wImR2;
        }
        if (y > 0 && x < maxXa)
        {
            sum += (unsigned int)*wImR3;
        }
        if (x > 0)
        {
            sum += (unsigned int)*wImR4;
        }
        if (x < maxXa)
        {
            sum += (unsigned int)*wImR5;
        }
        if (y < maxYa && x > 0)
        {
            sum += (unsigned int)*wImR6;
        }
        if (y < maxYa)
        {
            sum += (unsigned int)*wImR7;
        }
        if (y < maxYa && x < maxXa)
        {
            sum += (unsigned int)*wImR8;
        }

        if(sum)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;


        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
void RegionDilation13(Mat ImR)
{
// renewed version dilates whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxXb = maxX - 2;

    int maxYa = maxY - 1;
    int maxYb = maxY - 2;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0  = (unsigned short*)ImR.data;
    unsigned short *wImR1  = wImR0 - (2 * maxX);
    unsigned short *wImR2  = wImR0 - maxX - 1;
    unsigned short *wImR3  = wImR0 - maxX;
    unsigned short *wImR4  = wImR0 - maxX + 1;
    unsigned short *wImR5  = wImR0 - 2;
    unsigned short *wImR6  = wImR0 - 1;
    unsigned short *wImR7  = wImR0 + 1;
    unsigned short *wImR8  = wImR0 + 2;
    unsigned short *wImR9  = wImR0 + maxX - 1;
    unsigned short *wImR10 = wImR0 + maxX;
    unsigned short *wImR11 = wImR0 + maxX + 1;
    unsigned short *wImR12 = wImR0 + (2 * maxX);


    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int sum = (unsigned int)*wImR0;

        if (y > 1)
        {
            sum += (unsigned int)*wImR1;
        }
        if (y > 0 && x > 0)
        {
            sum += (unsigned int)*wImR2;
        }
        if (y > 0)
        {
            sum += (unsigned int)*wImR3;
        }
        if (y > 0 && x < maxXa)
        {
            sum += (unsigned int)*wImR4;
        }
        if (x > 1)
        {
            sum += (unsigned int)*wImR5;
        }
        if (x > 0)
        {
            sum += (unsigned int)*wImR6;
        }
        if (x < maxXa)
        {
            sum += (unsigned int)*wImR7;
        }
        if (x < maxXb)
        {
            sum += (unsigned int)*wImR8;
        }

        if (y < maxYa && x > 0)
        {
            sum += (unsigned int)*wImR9;
        }
        if (y < maxYa)
        {
            sum += (unsigned int)*wImR10;
        }
        if (y < maxYa && x < maxXa)
        {
            sum += (unsigned int)*wImR11;
        }
        if (y < maxYb)
        {
            sum += (unsigned int)*wImR12;
        }

        if(sum)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;


        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
        wImR9++;
        wImR10++;
        wImR11++;
        wImR12++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
void RegionErosion5(Mat ImR)
{
// renewed version erodes whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;;
    unsigned short *wImR1 = wImR0 - maxX;
    unsigned short *wImR2 = wImR0 - 1;
    unsigned short *wImR3 = wImR0 + 1;
    unsigned short *wImR4 = wImR0 + maxX;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = (unsigned int)*wImR0;
        if (y > 0)
        {
            product *= (unsigned int)*wImR1;
        }
        if (x > 0)
        {
            product *= (unsigned int)*wImR2;
        }
        if (x < maxXa)
        {
            product *= (unsigned int)*wImR3;
        }
        if (y < maxYa)
        {
            product *= (unsigned int)*wImR4;
        }
        if(product)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;

        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
void RegionErosion9(Mat ImR)
{
// renewed version erodes whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;;
    unsigned short *wImR1 = wImR0 - maxX - 1;
    unsigned short *wImR2 = wImR0 - maxX;
    unsigned short *wImR3 = wImR0 - maxX + 1;
    unsigned short *wImR4 = wImR0 - 1;
    unsigned short *wImR5 = wImR0 + 1;
    unsigned short *wImR6 = wImR0 + maxX - 1;
    unsigned short *wImR7 = wImR0 + maxX;
    unsigned short *wImR8 = wImR0 + maxX + 1;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = (unsigned int)*wImR0;
        if (y > 0 && x > 0)
        {
            product *= (unsigned int)*wImR1;
        }
        if (y > 0)
        {
            product *= (unsigned int)*wImR2;
        }
        if (y > 0 && x < maxXa)
        {
            product *= (unsigned int)*wImR3;
        }
        if (x > 0)
        {
            product *= (unsigned int)*wImR4;
        }
        if (x < maxXa)
        {
            product *= (unsigned int)*wImR5;
        }
        if (y < maxYa && x > 0)
        {
            product *= (unsigned int)*wImR6;
        }
        if (y < maxYa)
        {
            product *= (unsigned int)*wImR7;
        }
        if (y < maxYa && x < maxXa)
        {
            product *= (unsigned int)*wImR8;
        }

        if(product)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;


        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
void RegionErosion13(Mat ImR)
{
// renewed version erodes whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxXb = maxX - 2;

    int maxYa = maxY - 1;
    int maxYb = maxY - 2;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0  = (unsigned short*)ImR.data;
    unsigned short *wImR1  = wImR0 - (2 * maxX);
    unsigned short *wImR2  = wImR0 - maxX - 1;
    unsigned short *wImR3  = wImR0 - maxX;
    unsigned short *wImR4  = wImR0 - maxX + 1;
    unsigned short *wImR5  = wImR0 - 2;
    unsigned short *wImR6  = wImR0 - 1;
    unsigned short *wImR7  = wImR0 + 1;
    unsigned short *wImR8  = wImR0 + 2;
    unsigned short *wImR9  = wImR0 + maxX - 1;
    unsigned short *wImR10 = wImR0 + maxX;
    unsigned short *wImR11 = wImR0 + maxX + 1;
    unsigned short *wImR12 = wImR0 + (2 * maxX);


    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = (unsigned int)*wImR0;

        if (y > 1)
        {
            product *= (unsigned int)*wImR1;
        }
        if (y > 0 && x > 0)
        {
            product *= (unsigned int)*wImR2;
        }
        if (y > 0)
        {
            product *= (unsigned int)*wImR3;
        }
        if (y > 0 && x < maxXa)
        {
            product *= (unsigned int)*wImR4;
        }
        if (x > 1)
        {
            product *= (unsigned int)*wImR5;
        }
        if (x > 0)
        {
            product *= (unsigned int)*wImR6;
        }
        if (x < maxXa)
        {
            product *= (unsigned int)*wImR7;
        }
        if (x < maxXb)
        {
            product *= (unsigned int)*wImR8;
        }

        if (y < maxYa && x > 0)
        {
            product *= (unsigned int)*wImR9;
        }
        if (y < maxYa)
        {
            product *= (unsigned int)*wImR10;
        }
        if (y < maxYa && x < maxXa)
        {
            product *= (unsigned int)*wImR11;
        }
        if (y < maxYb)
        {
            product *= (unsigned int)*wImR12;
        }

        if(product)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;


        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
        wImR9++;
        wImR10++;
        wImR11++;
        wImR12++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------//---------------------------------------------------------------------------
void RegionErosionHorisontal13(Mat ImR)
{
// renewed version erodes whole imaga
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;
    int maxXa = maxX - 1;
    int maxXb = maxX - 2;

    int maxYa = maxY - 1;
    int maxYb = maxY - 2;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0  = (unsigned short*)ImR.data;
    unsigned short *wImR1  = wImR0 - (2 * maxX);
    unsigned short *wImR2  = wImR0 - maxX - 1;
    unsigned short *wImR3  = wImR0 - maxX;
    unsigned short *wImR4  = wImR0 - maxX + 1;
    unsigned short *wImR5  = wImR0 - 2;
    unsigned short *wImR6  = wImR0 - 1;
    unsigned short *wImR7  = wImR0 + 1;
    unsigned short *wImR8  = wImR0 + 2;
    unsigned short *wImR9  = wImR0 + maxX - 1;
    unsigned short *wImR10 = wImR0 + maxX;
    unsigned short *wImR11 = wImR0 + maxX + 1;
    unsigned short *wImR12 = wImR0 + (2 * maxX);


    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = (unsigned int)*wImR0;

        if (y > 1)
        {
            product *= (unsigned int)*wImR1;
        }
        if (y > 0 && x > 0)
        {
            product *= (unsigned int)*wImR2;
        }
        if (y > 0)
        {
            product *= (unsigned int)*wImR3;
        }
        if (y > 0 && x < maxXa)
        {
            product *= (unsigned int)*wImR4;
        }
        if (x > 1)
        {
            product *= (unsigned int)*wImR5;
        }
        if (x > 0)
        {
            product *= (unsigned int)*wImR6;
        }
        if (x < maxXa)
        {
            product *= (unsigned int)*wImR7;
        }
        if (x < maxXb)
        {
            product *= (unsigned int)*wImR8;
        }

        if (y < maxYa && x > 0)
        {
            product *= (unsigned int)*wImR9;
        }
        if (y < maxYa)
        {
            product *= (unsigned int)*wImR10;
        }
        if (y < maxYa && x < maxXa)
        {
            product *= (unsigned int)*wImR11;
        }
        if (y < maxYb)
        {
            product *= (unsigned int)*wImR12;
        }

        if(product)
            *wImRTemp = 1;
        else
            *wImRTemp = 0;


        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
        wImR9++;
        wImR10++;
        wImR11++;
        wImR12++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
Mat GetContour5(Mat ImR)
{
    //modyfied version works on whole image
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;

    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    Mat ImOut = Mat::zeros(maxY,maxX, CV_16U);

    unsigned short *wImOut = (unsigned short*)ImOut.data;



    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX;
    unsigned short *wImR2 = wImR0 - 1;
    unsigned short *wImR3 = wImR0 + 1;
    unsigned short *wImR4 = wImR0 + maxX;

    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;

        unsigned int product = 1;
        if (y > 0 && *wImR0 != *wImR1)
        {
            product *= 0;
        }
        if (x > 0 && *wImR0 != *wImR2)
        {
            product *= 0;
        }
        if (x < maxXa && *wImR0 != *wImR3)
        {
            product *= 0;
        }
        if (y < maxYa && *wImR0 != *wImR4)
        {
            product *= 0;
        }
        if(!product && *wImR0)
            *wImOut = *wImR0;
        else
            *wImOut = 0;

        wImOut++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
    }
    return ImOut;
}
//------------------------------------------------------------------------------
void GetContour9(Mat ImR)
{
    int maxX = ImR.cols;
    int maxY = ImR.rows;
    int maxXY = maxX * maxY;

    int maxXa = maxX - 1;
    int maxYa = maxY - 1;

    unsigned short *ImRTemp = new unsigned short[maxXY];

    unsigned short *wImRTemp = ImRTemp;

    unsigned short *wImR0 = (unsigned short*)ImR.data;
    unsigned short *wImR1 = wImR0 - maxX - 1;
    unsigned short *wImR2 = wImR0 - maxX;
    unsigned short *wImR3 = wImR0 - maxX + 1;
    unsigned short *wImR4 = wImR0 - 1;
    unsigned short *wImR5 = wImR0 + 1;
    unsigned short *wImR6 = wImR0 + maxX - 1;
    unsigned short *wImR7 = wImR0 + maxX;
    unsigned short *wImR8 = wImR0 + maxX + 1;


    for (int i = 0; i < maxXY; i++)
    {
        int x = i % maxX;
        int y = i / maxX;
        if (x > 0 && x < maxXa && y > 0 && y < maxYa)
        {
            if(*wImR0 && !(*wImR1 *  *wImR2 * *wImR3  * *wImR4
                      * *wImR5 *  *wImR6 * *wImR7  * *wImR8))
                *wImRTemp = *wImR0;
            else
                *wImRTemp = 0;
        }
        else
            *wImRTemp = 0;

        wImRTemp++;

        wImR0++;
        wImR1++;
        wImR2++;
        wImR3++;
        wImR4++;
        wImR5++;
        wImR6++;
        wImR7++;
        wImR8++;
    }
    wImRTemp = ImRTemp;
    wImR0 = (unsigned short*)ImR.data;
    for (int i = 0; i < maxXY; i++)
    {
        *wImR0 = *wImRTemp;
        wImRTemp++;
        wImR0++;
    }
    delete[] ImRTemp;
}
*/
//---------------------------------------------------------------------------
int CenterOfMas(Mat ImReg, int *centerX, int *centerY)
{
    unsigned short *wImReg = (unsigned short *)ImReg.data;
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    //int maxXY = maxX * maxY;

    int pixCount = 0;
    int posX = 0;
    int posY = 0;
    for(int y = 0; y <maxY; y++)
    {
        for(int x = 0; x <maxX; x++)
        {
            if(*wImReg)
            {
                pixCount++;
                posX += x;
                posY += y;
            }
            wImReg++;
        }
    }
    *centerX = posX / pixCount;
    *centerY = posY / pixCount;
    return 1;
}
//---------------------------------------------------------------------------
int CenterOfMas(Mat ImReg, int *centerX, int *centerY, unsigned short reg)
{
	unsigned short *wImReg = (unsigned short *)ImReg.data;
	int maxX = ImReg.cols;
	int maxY = ImReg.rows;
	//int maxXY = maxX * maxY;

	int pixCount = 0;
	int posX = 0;
	int posY = 0;
	for (int y = 0; y <maxY; y++)
	{
		for (int x = 0; x <maxX; x++)
		{
			if (*wImReg == reg)
			{
				pixCount++;
				posX += x;
				posY += y;
			}
			wImReg++;
		}
	}
	*centerX = posX / pixCount;
	*centerY = posY / pixCount;
	return 1;
}
//---------------------------------------------------------------------------
int PartOfRegionAtTheAngle(Mat ImReg, Mat ImRegOut,  int centerX, int centerY,
                           int directionDeg, int angleDeg,
                           unsigned short inRegNr, unsigned short outRegNr)
{
    int maxX = ImReg.cols;
    int maxY = ImReg.rows;
    //int centerX, centerY;
    //CenterOfMas(ImReg, maxX, maxY, &centerX, &centerY);

    int fi1Dec = directionDeg - angleDeg - 90;// - M_PI_2;
    int fi2Dec = directionDeg + angleDeg - 90;// - M_PI_2;


    double fi1 = (double)fi1Dec * 3.14159 /double(180);
    double fi2 = (double)fi2Dec * 3.14159 /double(180);

    double m1, m2, n1, n2;
    if(cos(fi1) != 0)
    {
        m1 = tan(fi1);
    }
    else
    {
        m1 = 100000;
    }
    n1 = centerY - int((double)centerX * m1);

    if(cos(fi2) != 0)
    {
        m2 = tan(fi2);
    }
    else
    {
        m2 = 100000;
    }
    n2 = centerY - int((double)centerX * m2);


    //*(ImReg + centerX + centerY * maxX) = 7;
    unsigned short *wImReg = (unsigned short *)ImReg.data;
    unsigned short *wImRegOut = (unsigned short *)ImRegOut.data;
    for(int y = 0; y <maxY; y++)
    {
        for(int x = 0; x <maxX; x++)
        {
            bool cond1 = 0;
            bool cond2 = 0;
            if(cos(fi1) < 0 && cos(fi2) < 0)
            {
                cond1 = (y <  int((double)x*m1 + n1));
                cond2 = (y >= int((double)x*m2 + n2));
            }
            if(cos(fi1) < 0 && cos(fi2) >= 0)
            {
                cond1 = (y <  int((double)x*m1 + n1));
                cond2 = (y < int((double)x*m2 + n2));
            }
            if(cos(fi1) >= 0 && cos(fi2) >= 0)
            {
                cond1 = (y >=  int((double)x*m1 + n1));
                cond2 = (y < int((double)x*m2 + n2));
            }
            if(cos(fi1) >= 0 && cos(fi2) < 0)
            {
                cond1 = (y >=  int((double)x*m1 + n1));
                cond2 = (y >= int((double)x*m2 + n2));
            }

            if( cond1 && cond2 && (*wImReg == inRegNr))
            {
                *wImRegOut = outRegNr;
            }
            wImReg++;
            wImRegOut++;

        }
    }
    return 1;
}
//---------------------------------------------------------------------------

cv::Mat CreateRoi16(int Shape, int maxX, int maxY)
{
    Mat Roi;
    int roiMaxX, roiMaxY; // Bounding box sizes for ROI
    switch (Shape) // Different tile shapes
    {
    case 1: // Rectangle
        roiMaxX = maxX;
        roiMaxY = maxY;
        Roi = Mat::ones(roiMaxY, roiMaxX, CV_16U);
        break;
    case 2: // Ellipse
        roiMaxX = maxX;
        roiMaxY = maxY;
        Roi = Mat::zeros(roiMaxY, roiMaxX, CV_16U);
        ellipse(Roi, Point(roiMaxX / 2, roiMaxY / 2),
            Size(roiMaxX / 2, roiMaxY / 2), 0.0, 0.0, 360.0,
            1, -1);
        break;
    case 3: // Hexagon
        {
            int edgeLength = maxX;
            roiMaxX = edgeLength * 2;
            roiMaxY = (int)((float)edgeLength * 0.8660254 * 2.0);
            Roi = Mat::zeros(roiMaxY, roiMaxX, CV_16U);

            Point vertice0(edgeLength / 2, 0);
            Point vertice1(edgeLength / 2 + edgeLength - 1, 0);
            Point vertice2(roiMaxX - 1, roiMaxY / 2);
            Point vertice3(edgeLength / 2 + edgeLength - 1, roiMaxY - 1);
            Point vertice4(edgeLength / 2, roiMaxY - 1);
            Point vertice5(0, roiMaxY / 2);

            line(Roi, vertice0, vertice1, 1, 1);
            line(Roi, vertice1, vertice2, 1, 1);
            line(Roi, vertice2, vertice3, 1, 1);
            line(Roi, vertice3, vertice4, 1, 1);
            line(Roi, vertice4, vertice5, 1, 1);
            line(Roi, vertice5, vertice0, 1, 1);
            unsigned short *wRoi;

            for (int y = 1; y < roiMaxY - 1; y++)
            {
                wRoi = (unsigned short *)Roi.data + roiMaxX * y;
                int x = 0;
                for (x; x < roiMaxX; x++)
                {
                    if (*wRoi)
                        break;
                    wRoi++;
                }
                x++;
                wRoi++;
                for (x; x < roiMaxX; x++)
                {
                    if (*wRoi)
                        break;
                    *wRoi = 1;
                    wRoi++;
                }
            }

        }
        break;
    case 4: // klepsydra
        {
            roiMaxX = maxX;
            roiMaxY = maxY;
            Roi = Mat::zeros(roiMaxY, roiMaxX, CV_16U);

            Point vertice0(0, 0);
            Point vertice1(roiMaxX - 1, roiMaxY - 1);
            Point vertice2(0, roiMaxY - 1);
            Point vertice3(roiMaxX - 1, 0);

            Point ShapePoints[1][5];
            ShapePoints[0][0] = Point(0,0);
            ShapePoints[0][1] = Point(0,roiMaxY-1);
            ShapePoints[0][2] = Point(roiMaxX-1,0);
            ShapePoints[0][3] = Point(roiMaxX-1,roiMaxY-1);
            ShapePoints[0][4] = Point(0,0);

            const Point* wShapePoints[1] = { ShapePoints[0] };
            int nrOfVertices[] = {5};
            fillPoly(Roi, wShapePoints, nrOfVertices,1,1,1);

        }
        break;
    default:
        break;
    }
    return Roi;
}
//---------------------------------------------------------------------------
cv::Mat Threshold16(cv::Mat ImIn, unsigned short threshold)
{
    if(ImIn.empty())
        return Mat::zeros(1,1,CV_16U);
    int maxX = ImIn.cols;
    int maxY = ImIn.rows;
    int maxXY = maxX * maxY;

    unsigned short *wImIn = (unsigned short*)ImIn.data;

    Mat Mask = Mat::zeros(maxY, maxX, CV_16U);
    unsigned short *wMask = (unsigned short*)Mask.data;

    for(int i = 0; i < maxXY; i++)
    {
        if(*wImIn > threshold)
            *wMask = 1;
        wImIn++;
        wMask++;
    }
    return Mask;
}
//---------------------------------------------------------------------------
void Threshold16(cv::Mat ImIn, cv::Mat Mask, unsigned short threshold)
{
    if(ImIn.empty())
        return;
    if(Mask.empty())
        return;
    int maxX = ImIn.cols;
    int maxY = ImIn.rows;
    int maxXY = maxX * maxY;

    if(Mask.cols != maxX || Mask.rows != maxY )
        return;



    unsigned short *wImIn = (unsigned short*)ImIn.data;

    unsigned short *wMask = (unsigned short*)Mask.data;

    for(int i = 0; i < maxXY; i++)
    {
        if(*wImIn > threshold)
            *wMask = 1;
        wImIn++;
        wMask++;
    }


}
//---------------------------------------------------------------------------
cv::Mat BuildKernel(int shape)
{
    Mat Kernel;

    switch(shape)
    {
    case 50:
        Kernel = (cv::Mat_<uchar>(15,15) << 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
        break;
    case 49:
        Kernel = (cv::Mat_<uchar>(15,15) << 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0);
        break;
    case 48:
        Kernel = (cv::Mat_<uchar>(15,15) << 0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0);
        break;
    case 47:
        Kernel = (cv::Mat_<uchar>(15,15) << 0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,1,1,1,1,0,0,0);
        break;
    case 46:
        Kernel = (cv::Mat_<uchar>(15,15) << 0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
                                            0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
                                            0,0,0,0,1,1,1,1,1,1,1,0,0,0,0);
        break;
    case 45:
        Kernel = (cv::Mat_<uchar>(15,15) << 0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
                                            0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
                                            0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
                                            0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
                                            0,0,0,0,0,1,1,1,1,1,0,0,0,0,0);
        break;
    case 40:
        Kernel = (cv::Mat_<uchar>(13,13) << 1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,1,1);
        break;
    case 20:
        Kernel = (cv::Mat_<uchar>(11,11) << 1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1);
        break;
    case 19:
        Kernel = (cv::Mat_<uchar>(11,11) << 0,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,0);
        break;
    case 18:
        Kernel = (cv::Mat_<uchar>(11,11) << 0,0,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,0,0);
        break;
    case 17:
        Kernel = (cv::Mat_<uchar>(11,11) << 0,0,0,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,0,0,0);
        break;
    case 16:
        Kernel = (cv::Mat_<uchar>(11,11) << 0,0,0,0,1,1,1,0,0,0,0,
                                            0,0,0,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,0,0,0,
                                            0,0,0,0,1,1,1,0,0,0,0);
        break;
    case 15:
        Kernel = (cv::Mat_<uchar>(11,11) << 0,0,0,0,0,1,0,0,0,0,0,
                                            0,0,0,0,1,1,1,0,0,0,0,
                                            0,0,0,1,1,1,1,1,0,0,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            1,1,1,1,1,1,1,1,1,1,1,
                                            0,1,1,1,1,1,1,1,1,1,0,
                                            0,0,1,1,1,1,1,1,1,0,0,
                                            0,0,0,1,1,1,1,1,0,0,0,
                                            0,0,0,0,1,1,1,0,0,0,0,
                                            0,0,0,0,0,1,0,0,0,0,0);
        break;
    case 14:
        Kernel = (cv::Mat_<uchar>(9,9) << 1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1);
        break;


    case 13:
        Kernel = (cv::Mat_<uchar>(9,9) << 0,1,1,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,1,1,0);
        break;

    case 12:
        Kernel = (cv::Mat_<uchar>(9,9) << 0,0,1,1,1,1,1,0,0,
                                          0,1,1,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,1,1,0,
                                          0,0,1,1,1,1,1,0,0);
        break;
    case 11:
        Kernel = (cv::Mat_<uchar>(9,9) << 0,0,0,1,1,1,0,0,0,
                                          0,0,1,1,1,1,1,0,0,
                                          0,1,1,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,1,1,0,
                                          0,0,1,1,1,1,1,0,0,
                                          0,0,0,1,1,1,0,0,0);
        break;
    case 10:
        Kernel = (cv::Mat_<uchar>(9,9) << 0,0,0,0,1,0,0,0,0,
                                          0,0,0,1,1,1,0,0,0,
                                          0,0,1,1,1,1,1,0,0,
                                          0,1,1,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,1,1,0,
                                          0,0,1,1,1,1,1,0,0,
                                          0,0,0,1,1,1,0,0,0,
                                          0,0,0,0,1,0,0,0,0);
        break;
    case 9:
        Kernel = (cv::Mat_<uchar>(7,7) << 1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1);
        break;
    case 8:
        Kernel = (cv::Mat_<uchar>(7,7) << 0,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,0);
        break;
    case 7:
        Kernel = (cv::Mat_<uchar>(7,7) << 0,0,1,1,1,0,0,
                                          0,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,0,
                                          0,0,1,1,1,0,0);
        break;
    case 6:
        Kernel = (cv::Mat_<uchar>(7,7) << 0,0,0,1,0,0,0,
                                          0,0,1,1,1,0,0,
                                          0,1,1,1,1,1,0,
                                          1,1,1,1,1,1,1,
                                          0,1,1,1,1,1,0,
                                          0,0,1,1,1,0,0,
                                          0,0,0,1,0,0,0);
        break;
    case 5:
        Kernel = (cv::Mat_<uchar>(5,5) << 1,1,1,1,1,
                                          1,1,1,1,1,
                                          1,1,1,1,1,
                                          1,1,1,1,1,
                                          1,1,1,1,1);
        break;
    case 4:
        Kernel = (cv::Mat_<uchar>(5,5) << 0,1,1,1,0,
                                          1,1,1,1,1,
                                          1,1,1,1,1,
                                          1,1,1,1,1,
                                          0,1,1,1,0);
        break;
    case 3:
        Kernel = (cv::Mat_<uchar>(5,5) << 0,0,1,0,0,
                                          0,1,1,1,0,
                                          1,1,1,1,1,
                                          0,1,1,1,0,
                                          0,0,1,0,0);
        break;
    case 2:
        Kernel = (cv::Mat_<uchar>(3,3) << 1,1,1,
                                          1,1,1,
                                          1,1,1);
        break;
    default:
        Kernel = (cv::Mat_<uchar>(3,3) << 0,1,0,
                                          1,1,1,
                                          0,1,0);
        break;
    }
    return Kernel;
}
//---------------------------------------------------------------------------
cv::Mat BuildRoundedKernell(int radius)
{
    int diameter = radius * 2 + 1;
    int center = radius + 1;
    Mat Kernel = Mat::zeros(diameter, diameter, CV_8U);
    ellipse(Kernel, Point(center,center), Size(radius,radius), 0.0, 0.0, 360.0, 1, -1);
    return Kernel;
}
//---------------------------------------------------------------------------
void DilationCV(cv::Mat Mask, int shape)
{
    Mat Kernel =  BuildKernel(shape);
    dilate(Mask,Mask,Kernel);
    return ;
}
//---------------------------------------------------------------------------
void ErosionCV(cv::Mat Mask, int shape)
{
    Mat Kernel =  BuildKernel(shape);
    erode(Mask,Mask,Kernel);
    return ;
}
//---------------------------------------------------------------------------
void DilationCircleCV(cv::Mat Mask, int radius)
{
    Mat Kernel =  BuildRoundedKernell(radius);
    dilate(Mask,Mask,Kernel);
    return ;
}
//---------------------------------------------------------------------------
void ErosionCircleCV(cv::Mat Mask, int radius)
{
    Mat Kernel =  BuildRoundedKernell(radius);
    erode(Mask,Mask,Kernel);
    return ;
}

cv::Mat MaskOutsideMatOut(cv::Mat Im, cv::Mat Mask)
{
    if(Im.empty())
        return Mat::zeros(0,0,CV_16U);
    if(Mask.empty())
        return Mat::zeros(0,0,CV_16U);
    if(Im.type() != CV_16U)
        return Mat::zeros(0,0,CV_16U);
    if(Mask.type() != CV_16U)
        return Mat::zeros(0,0,CV_16U);
    if(Im.cols != Mask.cols)
        return Mat::zeros(0,0,CV_16U);
    if(Im.rows != Mask.rows)
        return Mat::zeros(0,0,CV_16U);

    int maxXY = Im.cols *Im.rows;

    Mat Out = Mat::zeros(Im.rows,Im.cols,CV_16U);

    unsigned short *wIm = (unsigned short *)Im.data;
    unsigned short *wMask = (unsigned short *)Mask.data;
    unsigned short *wOut = (unsigned short *)Out.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(!*wMask)
            *wOut = *wIm;

        wMask++;
        wIm++;
        wOut++;
    }

    return Out;

}

int MaskOutside(cv::Mat Im, cv::Mat Mask)
{
    if(Im.empty())
        return -1;
    if(Mask.empty())
        return -2;
    if(Im.type() != CV_16U)
        return -3;
    if(Mask.type() != CV_16U)
        return -4;
    if(Im.cols != Mask.cols)
        return -5;
    if(Im.rows != Mask.rows)
        return -6;

    int maxXY = Im.cols *Im.rows;


    unsigned short *wIm = (unsigned short *)Im.data;
    unsigned short *wMask = (unsigned short *)Mask.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(*wMask)
            *wIm = 0;

        wMask++;
        wIm++;

    }

    return 1;

}

//----------------------------------------------------------------------------------------------------------------------
int MaskInside(cv::Mat Im, cv::Mat Mask)
{
    if(Im.empty())
        return -1;
    if(Mask.empty())
        return -2;
    if(Im.type() != CV_16U)
        return -3;
    if(Mask.type() != CV_16U)
        return -4;
    if(Im.cols != Mask.cols)
        return -5;
    if(Im.rows != Mask.rows)
        return -6;

    int maxXY = Im.cols *Im.rows;

    unsigned short *wIm = (unsigned short *)Im.data;
    unsigned short *wMask = (unsigned short *)Mask.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(!*wMask)
            *wIm = 0;
        wMask++;
        wIm++;
    }
    return 1;
}
//----------------------------------------------------------------------------------------------------------------------
int MaskMaskInv(Mat Mask, Mat Mask2)
{
    if(Mask.empty())
        return -1;
    if(Mask2.empty())
        return -2;
    if(Mask.type() != CV_16U)
        return -3;
    if(Mask2.type() != CV_16U)
        return -4;
    if(Mask2.cols != Mask.cols)
        return -5;
    if(Mask2.rows != Mask.rows)
        return -6;

    int maxXY = Mask.cols * Mask.rows;

    unsigned short *wMask = (unsigned short *)Mask.data;
    unsigned short *wMask2 = (unsigned short *)Mask2.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(*wMask2)
            *wMask = 0;
        wMask++;
        wMask2++;
    }
    return 1;
}
//----------------------------------------------------------------------------------------------------------------------
cv::Mat MaskInv(cv::Mat Mask)
{
    Mat MaskOut;

    if(Mask.empty())
        return MaskOut;
    if(Mask.type() != CV_16U)
        return MaskOut;

    int maxXY = Mask.cols * Mask.rows;

    MaskOut = Mat::zeros(Mask.rows, Mask.cols, CV_16U);
    unsigned short *wMask = (unsigned short *)Mask.data;
    unsigned short *wMaskOut = (unsigned short *)MaskOut.data;
    for(int i = 0; i < maxXY; i++)
    {
        if(*wMask)
            *wMaskOut = 0;
        else
            *wMaskOut = 1;

        wMask++;
        wMaskOut++;
    }
    return MaskOut;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
cv::Mat Combine2Regions(cv::Mat Mask1, cv::Mat Mask2)
{
    Mat Out;

    if(Mask1.empty() || Mask2.empty())
        return Out;
    if(Mask1.type() != CV_16U || Mask2.type() != CV_16U)
        return Out;
    if(Mask1.cols != Mask2.cols || Mask1.rows != Mask2.rows)
        return Out;

    int maxX = Mask1.cols;
    int maxY = Mask1.rows;

    Out = Mat::zeros(maxY, maxX, CV_16U);
    int maxXY = maxX * maxY;

    uint16_t  *wMask1 = (uint16_t  *)Mask1.data;
    uint16_t  *wMask2 = (uint16_t  *)Mask2.data;
    uint16_t  *wOut = (uint16_t  *)Out.data;

    for(int i = 0; i < maxXY; i++)
    {
        if(*wMask1 || *wMask2)
            *wOut = 1;
        wMask1++;
        wMask2++;
        wOut++;
    }
    return Out;

}
//----------------------------------------------------------------------------------------------------------------------
