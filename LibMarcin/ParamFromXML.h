#ifndef ParamFromXML
#define ParamFromXML
#include <iostream>
#include <string>

using namespace std;



class ProcessOptions
{
public:
	string InFolderName1;
	string FileNameBase1;
	string InFileExtension1;
	string InFilePattern1;

	string InFolderName2;
	string FileNameBase2;
	string InFileExtension2;
	string InFilePattern2;

	string InFolderName3;
	string FileNameBase3;
	string InFileExtension3;
	string InFilePattern3;

	string InFolderName4;
	string FileNameBase4;
	string InFileExtension4;
	string InFilePattern4;

	string InFolderName5;
	string FileNameBase5;
	string InFileExtension5;
	string InFilePattern5;

	string InFolderName6;
	string FileNameBase6;
	string InFileExtension6;
	string InFilePattern6;

	string OutFolderName1;
	string OutFolderName2;

	int preprocessType;
	int preprocessKernelSize;

	bool displayResult;
	bool displaySmallImage;

	int tileShape;

	int maxTileX;
	int maxTileY;

	int tileShiftX;
	int tileShiftY;

	bool showTiles;

	bool goThru;

	bool useSecondImage;

	bool textOut;
	int normalisation;

	int binCount;

	int minOfset;
	int maxOfset;
	bool useContrast;
	bool useEnergy;
	bool useHomogeneity;
	bool useCorrelation;
	int minHit;

	bool useMinMean;
	float minMean;

	float minNorm;
	float maxNorm ;

	float minNormGlobal;
	float maxNormGlobal;

	bool useFixtDispNorm;

	float displayMax;
	float displayMin;

	float displayMax2;
	float displayMin2;

	float displayMax3;
	float displayMin3;

	float displayMax4;
	float displayMin4;

	int tileLineThickness;
	int lineHalfLength;

	float angleStep;
	int interpolation;

	float treshold1;
	float treshold2;
	// functions
	//void szaiba(void);
	ProcessOptions();
	int LoadParams(string XmlFileName);
	string ShowParams(void);

};

#endif

