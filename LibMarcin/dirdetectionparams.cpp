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
    displayGrayMax = 65535;
    displayGrayMin = 0;

    showInputPC = false;
    displayPCMax = 65535;
    displayPCMin = 0;

    tileShape = 1;
    tileSize = 61;
    tileShift = 64;
    tileOffsetX = 32;
    tileOffsetY = 32;

    showTileRoiImage = false;

    showTilesOnImage = true;
    tileLineWidth = 1;

    imagesScale = 1.0;

    normalisation = 3;
    fixMinNorm =0;
    fixMaxNorm = 65535.0;

    binCount = 16;

    angleStep = 1.0;

    minOffset = 8;
    offsetCount = 8;
    offsetStep = 1;

    showOutputImage = false;
    directionLineWidth = 3;
    directionLineLength = 23;

    showTileOutputImage = false;

    showOutputText = false;

    textOut = true;
    imgOut = false;

    granularityCalc = false;
    granularityFirstOfset = 1;
    granularityOffsetCount = 10;
    granularityOffsetStep = 1;
    maZdaStyleOut = false;

    className.clear();
    dataSeparator = "\t";

}

std::string DirDetectionParams::ShowParams()
{
    string OutString = "";

    OutString += "Input Directory :" + dataSeparator + InFolderName	 + dataSeparator + "\n";
    OutString += "Input File Name Pattern :"  + dataSeparator + InFilePattern  + dataSeparator + "\n";

    OutString += "Output Directory:" + dataSeparator + OutFolderName + dataSeparator + "\n";

   // analisis parameters
    OutString += "Preprocess Type:" + dataSeparator ;
    OutString += to_string(preprocessType);
    OutString += dataSeparator + " - ";
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
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Preprocess kernel size:";
    OutString += dataSeparator;
    OutString += to_string(preprocessKernelSize);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile Shape:";
    OutString += dataSeparator;
    OutString += to_string(tileShape);
    OutString += dataSeparator;
    OutString += " - ";
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
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile width x:";
    OutString += dataSeparator;
    OutString += to_string(tileSize);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile shift:";
    OutString += dataSeparator;
    OutString += to_string(tileShift);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile offset x:";
    OutString += dataSeparator;
    OutString += to_string(tileOffsetX);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile offset y:";
    OutString += dataSeparator;
    OutString += to_string(tileOffsetY);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Normalisation:";
    OutString += dataSeparator;
    OutString += to_string(normalisation);
    OutString += dataSeparator;
    OutString += " - ";
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
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Fixed Min Norm:";
    OutString += dataSeparator;
    OutString += to_string(fixMinNorm);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Fixed Max Norm:";
    OutString += dataSeparator;
    OutString += to_string(fixMaxNorm);
    OutString += dataSeparator;
    OutString += "\n";


    OutString += "Bin count:";
    OutString += dataSeparator;
    OutString += to_string(binCount);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Min Offset:";
    OutString += dataSeparator;
    OutString += to_string(minOffset);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Offset count:";
    OutString += dataSeparator;
    OutString += to_string(offsetCount);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Offset step:";
    OutString += dataSeparator;
    OutString += to_string(offsetStep);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Angle Step:";
    OutString += dataSeparator;
    OutString += to_string(angleStep);
    OutString += dataSeparator;
    OutString += "\n";

// display options
    OutString += "Display Input Image in gray:";
    OutString += dataSeparator;
    if (showInputGray)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Display range Max Gray:";
    OutString += dataSeparator;
    OutString += to_string(displayGrayMax);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Display range Min Gray:";
    OutString += dataSeparator;
    OutString += to_string(displayGrayMin);
    OutString += dataSeparator;
    OutString += "\n";


    OutString += "Display Input Image in pseudocolor:";
    OutString += dataSeparator;
    if (showInputPC)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Display range Max pseudocolor image:";
    OutString += dataSeparator;
    OutString += to_string(displayPCMax);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Display range Min pseudocolor image:";
    OutString += dataSeparator;
    OutString += to_string(displayPCMin);
    OutString += dataSeparator;
    OutString += "\n";


    OutString += "Display Roi Shape Image:";
    OutString += dataSeparator;
    if (showTileRoiImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Show tiles:";
    OutString += dataSeparator;
    if (showTilesOnImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Tile Line Width>:";
    OutString += dataSeparator;
    OutString += to_string(tileLineWidth);
    OutString += dataSeparator;
    OutString += "\n";




    OutString += "Show output image:";
    OutString += dataSeparator;
    if (showOutputImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Direction Line Width>:";
    OutString += dataSeparator;
    OutString += to_string(directionLineWidth);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Direction Line Length:";
    OutString += dataSeparator;
    OutString += to_string(directionLineLength);
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Display small image:";
    OutString += dataSeparator;
    if (showTileOutputImage)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Show out text:";
    OutString += dataSeparator;
    if (showOutputText)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";


    OutString += "Text out:";
    OutString += dataSeparator;
    if (textOut)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "Image out:";
    OutString += dataSeparator;
    if (imgOut)
        OutString += "Y";
    else
        OutString += "N";
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "File Name:";
    OutString += dataSeparator;
    OutString += FileName;
    OutString += dataSeparator;
    OutString += "\n";

    OutString += "\n";
    return OutString;
}
