#include "dirdetectionparams.h"

using namespace std;

DirDetectionParams::DirDetectionParams()
{
    DefaultParams();
}

DirDetectionParams::~DirDetectionParams()
{
    InFolderName.empty();
    InFilePattern.empty();

    OutFolderName.empty();
}

void DirDetectionParams::DefaultParams(void)
{
    InFolderName = "";
    InFilePattern = ".+";

    OutFolderName = "";

    preprocessType = 0;
    preprocessKernelSize = 3;

    showInputGray = false;
    displayGrayMax = 40000;
    displayGrayMin = 0;

    showInputPC = false;
    displayPCMax = 65535;
    displayPCMin = 0;

    tileShape = 1;
    tileSize = 61;
    tileShift = 45;
    tileOffsetX = 31;
    tileOffsetY = 31;

    showTileRoiImage = false;

    showTilesOnImage = true;
    tileLineWidth = 1;

    normalisation = 3;
    fixMinNorm =0;
    fixMaxNorm = 65535.0;

    binCount = 16;

    angleStep = 1.0;

    minOffset = 8;
    offsetCount = 4;
    offsetStep = 1;

    showOutputImage = false;
    directionLineWidth = 2;
    directionLineLength = 23;

    showTileOutputImage = false;

    showOutputText = true;

    textOut = true;
    imgOut = false;

}

std::string DirDetectionParams::ShowParams()
{
    string OutString = "";

    OutString += "Input Directory :\t"		+ InFolderName		+ "\n";
    OutString += "Input File Name Pattern :\t"	+ InFilePattern	+ "\n";

    OutString += "Output Directory:\t" + OutFolderName + "\n";

   // analisis parameters
    OutString += "Preprocess Type:\t";
    OutString += to_string(preprocessType);
    OutString += "\t - ";
    switch (preprocessType)
    {
    case 1:
        OutString += "average blurr";
        break;
    case 2:
        OutString += "median blurr";
        break;
    default:
        OutString += "none";
        break;
    }
    OutString += "\n";

    OutString += "Preprocess kernel size:\t";
    OutString += to_string(preprocessKernelSize);
    OutString += "\n";

    OutString += "Tile Shape:\t";
    OutString += to_string(tileShape);
    OutString += "\t - ";
    switch (tileShape)
    {
    case 1:
        OutString += "Circular";
        break;
    case 2:
        OutString += "Hexagonal";
        break;
    default:
        OutString += "Squared";
        break;
    }
    OutString += "\n";

    OutString += "Tile width x:\t";
    OutString += to_string(tileSize);
    OutString += "\n";

    OutString += "Tile shift:\t";
    OutString += to_string(tileShift);
    OutString += "\n";

    OutString += "Tile offset x:\t";
    OutString += to_string(tileOffsetX);
    OutString += "\n";

    OutString += "Tile offset y:\t";
    OutString += to_string(tileOffsetY);
    OutString += "\n";

    OutString += "Normalisation:\t";
    OutString += to_string(normalisation);
    OutString += "\t - ";
    switch (normalisation)
    {
    case 1:
        OutString += "Tile min - max";
        break;
    case 2:
        OutString += "Global min - max";
        break;
    case 3:
        OutString += "Tile +/- 3 sigma";
        break;
    case 4:
        OutString += "Global +/- 3 sigma";
        break;
    case 5:
        OutString += "Tile 1%-99%";
        break;
    case 6:
        OutString += "Global 1%-99%";
        break;
    default:
        OutString += "none";
        break;
    }
    OutString += "\n";

    OutString += "Fixed Min Norm:\t";
    OutString += to_string(fixMinNorm);
    OutString += "\n";

    OutString += "Fixed Max Norm:\t";
    OutString += to_string(fixMaxNorm);
    OutString += "\n";


    OutString += "Bin count:\t";
    OutString += to_string(binCount);
    OutString += "\n";

    OutString += "Min Offset:\t";
    OutString += to_string(minOffset);
    OutString += "\n";

    OutString += "Offset count:\t";
    OutString += to_string(offsetCount);
    OutString += "\n";

    OutString += "Offset step:\t";
    OutString += to_string(offsetStep);
    OutString += "\n";

    OutString += "Angle Step:\t";
    OutString += to_string(angleStep);
    OutString += "\n";

// display options
    OutString += "Display Input Image in gray:\t";
    if (showInputGray)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Display range Max Gray:\t";
    OutString += to_string(displayGrayMax);
    OutString += "\n";

    OutString += "Display range Min Gray:\t";
    OutString += to_string(displayGrayMin);
    OutString += "\n";


    OutString += "Display Input Image in pseudocolor:\t";
    if (showInputPC)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Display range Max pseudocolor image:\t";
    OutString += to_string(displayPCMax);
    OutString += "\n";

    OutString += "Display range Min pseudocolor image:\t";
    OutString += to_string(displayPCMin);
    OutString += "\n";


    OutString += "Display Roi Shape Image:\t";
    if (showTileRoiImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Show tiles:\t";
    if (showTilesOnImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Tile Line Width>:\t";
    OutString += to_string(tileLineWidth);
    OutString += "\n";




    OutString += "Show output image:\t";
    if (showOutputImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Direction Line Width>:\t";
    OutString += to_string(directionLineWidth);
    OutString += "\n";

    OutString += "Direction Line Length:\t";
    OutString += to_string(directionLineLength);
    OutString += "\n";

    OutString += "Display small image:\t";
    if (showTileOutputImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Show out text:\t";
    if (showOutputText)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";


    OutString += "Text out:\t";
    if (textOut)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "Image out:\t";
    if (imgOut)
        OutString += "Y";
    else
        OutString += "N";
    OutString += "\n";

    OutString += "File Name:\t"	+ FileName	+ "\n";;

    OutString += "\n";
    return OutString;
}
