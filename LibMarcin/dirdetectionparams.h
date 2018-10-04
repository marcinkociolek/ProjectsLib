#ifndef DIRDETECTIONPARAMS_H
#define DIRDETECTIONPARAMS_H

#include <string>


class DirDetectionParams
{
public:
    // folders and file options
    std::string InFolderName;
    std::string InFilePattern;

    std::string OutFolderName;

    std::string FileName; //this is only for passing the finamame to the procedude not to store in xmlfile

    // analisis parameters
    int preprocessType;
    int preprocessKernelSize;

    int tileShape;
    int tileSize;
    int tileShift;
    int tileOffsetX;
    int tileOffsetY;

    int normalisation;
    float fixMinNorm;
    float fixMaxNorm ;

    int binCount;

    int minOffset;
    int offsetCount;
    int offsetStep;

    double angleStep;

    // display options

    bool showInputGray;
    float displayGrayMax;
    float displayGrayMin;

    bool showInputPC;
    float displayPCMax;
    float displayPCMin;

    bool showTileRoiImage;

    bool showTilesOnImage;
    int tileLineWidth;

    double imagesScale;

    bool showOutputImage;
    int directionLineWidth;
    int directionLineLength;

    bool showTileOutputImage;

    bool showOutputText;

    // output options
    bool textOut;
    bool imgOut;

    // functions
    DirDetectionParams();
    ~DirDetectionParams();
    void DefaultParams(void);
    //int LoadParams(string XmlFileName);
    //int SaveParams(string XmlFileName);
    std::string ShowParams(void);
};

#endif // DIRDETECTIONPARAMS_H
