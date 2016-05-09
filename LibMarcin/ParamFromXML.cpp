#include "ParamFromXML.h"
#include "..\tinyxml\tinyxml.h"
#include "..\tinyxml\tinystr.h"
#include <stdio.h>


#include <iostream>




using namespace std;

ProcessOptions::ProcessOptions()
{
	InFolderName1 = "";
	FileNameBase1 = "";
	InFileExtension1 = "";
	InFilePattern1 = "";

	InFolderName2 = "";
	FileNameBase2 = "";
	InFileExtension2 = "";
	InFilePattern2 = "";

	InFolderName3 = "";
	FileNameBase3 = "";
	InFileExtension3 = "";
	InFilePattern3 = "";

	InFolderName4 = "";
	FileNameBase4 = "";
	InFileExtension4 = "";
	InFilePattern4 = "";

	InFolderName5 = "";
	FileNameBase5 = "";
	InFileExtension5 = "";
	InFilePattern5 = "";

	InFolderName6 = "";
	FileNameBase6 = "";
	InFileExtension6 = "";
	InFilePattern6 = "";

	OutFolderName1 = "";
	OutFolderName2 = "";

	displayResult = 0;
	displaySmallImage = 0;

	tileShape = 1;

	maxTileX = 40;
	maxTileY = 40;

	shiftTileX = 40;
	shiftTileY = 40;

	offsetTileX = 40;
	offsetTileY = 40;

	
	showTiles = 1;
	tileLineThickness = 1;

	goThru = 1;

	useSecondImage = 0;

	preprocessType = 0;
	preprocessKernelSize = 3;

	textOut = 0;
	normalisation = 0;
	
	binCount = 16;

	minOfset = 2;
	maxOfset = 16;
	useContrast = 0;
	useEnergy = 0;
	useHomogeneity = 0;
	useCorrelation = 1;
	minHit = 0;

	useMinMean = 0;
	minMean = 0;

	minNorm = 0;
	maxNorm = 255;

	minNormGlobal = 0;
	maxNormGlobal = 255;

	useFixtDispNorm = 1;

	displayMax = 0;
	displayMin = 255;

	displayMax2 = 0;
	displayMin2 = 255;

	displayMax3 = 0;
	displayMin3 = 255;

	displayMax4 = 0;
	displayMin4 = 255;

	imposedLineThickness = 1;
	lineLengthPropToConfidence = 0;
	lineHalfLength = 20;
	
	angleStep = 1;
	interpolation = 0;

	treshold1 = 0;
	treshold2 = 0;
}
//-------------------------------------------------------------------------------------------------------------------
int ProcessOptions::LoadParams(string XmlFileName)
{
	string OutStr = "";
	
	TiXmlDocument doc(XmlFileName.c_str());
	doc.LoadFile();

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);
	TiXmlHandle hParameters(0);
	TiXmlHandle hPreprocess(0);

	pElem = hDoc.FirstChildElement().Element();

	OutStr += pElem->Value();
	OutStr += "\n";

	hRoot = TiXmlHandle(pElem);
	// file to open
	pElem = hRoot.FirstChild("input").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr += "No entry: input directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr +="Empty entry: input directory";
		OutStr += "\n";
	}
	else
		InFolderName1 = pElem->GetText();

	pElem = hRoot.FirstChild("input").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr +="No entry: input filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr +="Empty entry: input filename";
		OutStr += "\n";
	}
	else
		FileNameBase1 = pElem->GetText();
	
	pElem = hRoot.FirstChild("input").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr +="No entry: input filename";
		OutStr += "\n";
	}
	if(!pElem->GetText())
	{
		OutStr +="Empty entry: input filename";
		OutStr += "\n";
	}
	else
		InFileExtension1 = pElem->GetText();

	pElem = hRoot.FirstChild("input").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input pattern";
		OutStr += "\n";
	}
	else
		InFilePattern1 = pElem->GetText();

	// second file input
	pElem = hRoot.FirstChild("input2").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: input2 directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry:input2 directory";
		OutStr += "\n";
	}
	else
		InFolderName2 = pElem->GetText();

	pElem = hRoot.FirstChild("input2").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: input2 filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input2 filename";
		OutStr += "\n";
	}
	else
		FileNameBase2 = pElem->GetText();

	pElem = hRoot.FirstChild("input2").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: input2 extension";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input2 extension";
		OutStr += "\n";
	}
	else
		InFileExtension2 = pElem->GetText();

	pElem = hRoot.FirstChild("input2").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input2 pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input2 pattern";
		OutStr += "\n";
	}
	else
		InFilePattern2 = pElem->GetText();

	// 3rd file input
	pElem = hRoot.FirstChild("input3").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input3 directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry:input3 directory";
		OutStr += "\n";
	}
	else
		InFolderName3 = pElem->GetText();

	pElem = hRoot.FirstChild("input3").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input3 filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input3 filename";
		OutStr += "\n";
	}
	else
		FileNameBase3 = pElem->GetText();

	pElem = hRoot.FirstChild("input3").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input3 extension";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input3 extension";
		OutStr += "\n";
	}
	else
		InFileExtension3 = pElem->GetText();

	pElem = hRoot.FirstChild("input3").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input3 pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input3 pattern";
		OutStr += "\n";
	}
	else
		InFilePattern3 = pElem->GetText();

	// 4th file input
	pElem = hRoot.FirstChild("input4").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input4 directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry:input4 directory";
		OutStr += "\n";
	}
	else
		InFolderName4 = pElem->GetText();

	pElem = hRoot.FirstChild("input4").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input4 filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input4 filename";
		OutStr += "\n";
	}
	else
		FileNameBase4 = pElem->GetText();

	pElem = hRoot.FirstChild("input4").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input4 extension";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input4 extension";
		OutStr += "\n";
	}
	else
		InFileExtension4 = pElem->GetText();

	pElem = hRoot.FirstChild("input4").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input4 pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input4 pattern";
		OutStr += "\n";
	}
	else
		InFilePattern4 = pElem->GetText();

	// 5th file input
	pElem = hRoot.FirstChild("input5").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input5 directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry:input5 directory";
		OutStr += "\n";
	}
	else
		InFolderName5 = pElem->GetText();

	pElem = hRoot.FirstChild("input5").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input5 filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input5 filename";
		OutStr += "\n";
	}
	else
		FileNameBase5 = pElem->GetText();

	pElem = hRoot.FirstChild("input5").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input5 extension";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input5 extension";
		OutStr += "\n";
	}
	else
		InFileExtension5 = pElem->GetText();

	pElem = hRoot.FirstChild("input5").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input5 pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input5 pattern";
		OutStr += "\n";
	}
	else
		InFilePattern5 = pElem->GetText();

	// 6th file input
	pElem = hRoot.FirstChild("input6").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input6 directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry:input6 directory";
		OutStr += "\n";
	}
	else
		InFolderName6 = pElem->GetText();

	pElem = hRoot.FirstChild("input6").FirstChild("filebase").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input6 filename";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input6 filename";
		OutStr += "\n";
	}
	else
		FileNameBase6 = pElem->GetText();

	pElem = hRoot.FirstChild("input6").FirstChild("extension").Element();
	if (!pElem)
	{
		OutStr = +"No entry: input6 extension";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: input6 extension";
		OutStr += "\n";
	}
	else
		InFileExtension6 = pElem->GetText();

	pElem = hRoot.FirstChild("input6").FirstChild("pattern").Element();
	if (!pElem)
	{
		OutStr += "No entry: input6 pattern";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr += "Empty entry: input6 pattern";
		OutStr += "\n";
	}
	else
		InFilePattern6 = pElem->GetText();

	// output folder
	pElem = hRoot.FirstChild("output").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: output directory";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: output directory";
		OutStr += "\n";
	}
	else
		OutFolderName1 = pElem->GetText();
	// output folder 2
	pElem = hRoot.FirstChild("output2").FirstChild("directory").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: output directory2";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: output directory2";
		OutStr += "\n";
	}
	else
		OutFolderName2 = pElem->GetText();


	pElem = hRoot.FirstChild("preprocess").Element();
	if (!pElem)
	{
		OutStr = +"No entry: preprocess section";
		OutStr += "\n";
	}
	hPreprocess = TiXmlHandle(pElem);
	string ValStr;


	pElem = hPreprocess.FirstChild("preprocessType").Element();
	if (!pElem)
	{
		OutStr = +"No entry: preprocessType";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: preprocessType";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		preprocessType = stoi(ValStr);
	}

	pElem = hPreprocess.FirstChild("preprocessKernelSize").Element();
	if (!pElem)
	{
		OutStr = +"No entry: preprocessKernelSize";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: preprocessKernelSize";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		preprocessKernelSize = stoi(ValStr);
		if (preprocessKernelSize < 3)
			preprocessKernelSize = 3;
	}

	pElem = hRoot.FirstChild("parameters").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: parameters section";
		OutStr += "\n";
	}
	hParameters = TiXmlHandle(pElem);


	pElem = hParameters.FirstChild("displayResult").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: display result";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: display result";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			displayResult = 1;
		}
		else
			displayResult = 0;
	}

	pElem = hParameters.FirstChild("dispaySmallImage").Element();
	if (!pElem)
	{
		OutStr = +"No entry: display Small Image";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: display Small Image";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			displaySmallImage = 1;
		}
		else
			displaySmallImage = 0;
	}

	pElem = hParameters.FirstChild("tileShape").Element();
	if (!pElem)
	{
		OutStr = +"No entry:tileShape";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: tileShape";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		tileShape = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("maxTileX").Element();
	if (!pElem)
	{
		OutStr = +"No entry: maxTileX";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: maxTileX";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		maxTileX = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("maxTileY").Element();
	if (!pElem)
	{
		OutStr = +"No entry: MaxTileY";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: MaxTileY";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		maxTileY = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("shiftTileX").Element();
	if (!pElem)
	{
		OutStr = +"No entry: shiftTileX";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: shiftTileX";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		shiftTileX = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("shiftTileY").Element();
	if (!pElem)
	{
		OutStr = +"No entry: shiftTileY";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: shiftTileY";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		shiftTileY = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("offsetTileX").Element();
	if (!pElem)
	{
		OutStr = +"No entry: offsetTileX";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: offsetTileX";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		offsetTileX = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("offsetTileY").Element();
	if (!pElem)
	{
		OutStr = +"No entry: offsetTileY";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: offsetTileY";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		offsetTileY = stoi(ValStr);
	}



	pElem = hParameters.FirstChild("showTiles").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: showTiles";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"No entry: showTiles";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			showTiles = 1;
		}
		else
			showTiles = 0;
	}

	pElem = hParameters.FirstChild("tileLineThickness").Element();
	if (!pElem)
	{
		OutStr = +"No entry: tileLineThickness";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: tileLineThickness";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		tileLineThickness = stoi(ValStr);
	}


	pElem = hParameters.FirstChild("goThru").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: goThrou";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: goThrou";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			goThru = 1;
		}
		else
			goThru = 0;
	}

	pElem = hParameters.FirstChild("useSecondImage").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: use second image";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: use second image";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useSecondImage = 1;
		}
		else
			useSecondImage = 0;
	}

	pElem = hParameters.FirstChild("textOut").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: textOut";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: textOut";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			textOut = 1;
		}
		else
			textOut = 0;
	}

	pElem = hParameters.FirstChild("normalisation").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: normalisation";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: normalisation";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		normalisation = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("binCount").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: binCount";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: binCount";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		binCount = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("minOfset").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: minOfset";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: minOfset";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		minOfset = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("maxOfset").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: maxOfset";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: maxOfset";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		maxOfset = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("useContrast").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useContrast";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useContrast";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useContrast = 1;
		}
		else
			useContrast = 0;
	}
	
	pElem = hParameters.FirstChild("useEnergy").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useEnergy";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useEnergy";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useEnergy = 1;
		}
		else
			useEnergy = 0;
	}

	pElem = hParameters.FirstChild("useHomogeneity").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useHomogeneity";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useHomogeneity";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useHomogeneity = 1;
		}
		else
			useHomogeneity = 0;
	}

	pElem = hParameters.FirstChild("useCorrelation").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useCorrelation";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useCorrelation";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useCorrelation = 1;
		}
		else
			useCorrelation = 0;
	}

	pElem = hParameters.FirstChild("minHit").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: minHit";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: minHit";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		minHit = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("useMinMean").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useMinMean";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useMinMean";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useMinMean = 1;
		}
		else
			useMinMean = 0;
	}

	pElem = hParameters.FirstChild("minMean").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: minMean";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: minMean";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		minMean = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("minNorm").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: minNorm";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: minNorm";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		minNorm = stof(ValStr);
	}

	pElem = hParameters.FirstChild("maxNorm").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: maxNorm";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: maxNorm";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		maxNorm = stof(ValStr);
	}

	pElem = hParameters.FirstChild("minNormGlobal").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: minNormGlobal";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: minNormGlobal";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		minNormGlobal = stof(ValStr);
	}

	pElem = hParameters.FirstChild("maxNormGlobal").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: maxNormGlobal";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: maxNormGlobal";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		maxNormGlobal = stof(ValStr);
	}

	pElem = hParameters.FirstChild("useFixtDispNorm").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: useFixtDispNorm";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: useFixtDispNorm";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			useFixtDispNorm = 1;
		}
		else
			useFixtDispNorm = 0;
	}

	pElem = hParameters.FirstChild("displayMax").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: displayMax";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMax";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMax = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMin").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: displayMin";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMin";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMin = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMax2").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: displayMax2";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMax2";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMax2 = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMin2").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: displayMin2";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMin2";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMin2 = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMax3").Element();
	if (!pElem)
	{
		OutStr = +"No entry: displayMax3";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMax3";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMax3 = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMin3").Element();
	if (!pElem)
	{
		OutStr = +"No entry: displayMin3";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMin3";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMin3 = stof(ValStr);
	}

	//
	pElem = hParameters.FirstChild("displayMax4").Element();
	if (!pElem)
	{
		OutStr = +"No entry: displayMax4";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMax4";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMax4 = stof(ValStr);
	}

	pElem = hParameters.FirstChild("displayMin4").Element();
	if (!pElem)
	{
		OutStr = +"No entry: displayMin4";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: displayMin4";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		displayMin4 = stof(ValStr);
	}



	pElem = hParameters.FirstChild("imposedLineThickness").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: iposedLineThickness";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr =+ "Empty entry: iposedLineThickness";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		imposedLineThickness = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("lineLengthPropToConfidence").Element();
	if (!pElem)
	{
		OutStr = +"No entry: lineLength Prop To Confidence";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: line LengthProp To Confidence";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		if (ValStr == "Y")
		{
			lineLengthPropToConfidence = 1;
		}
		else
			lineLengthPropToConfidence = 0;
	}


	pElem = hParameters.FirstChild("lineHalfLength").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: lineHalfLength";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: lineHalfLength";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		lineHalfLength = stoi(ValStr);
	}

	pElem = hParameters.FirstChild("angleStep").Element();
	if (!pElem)
	{
		OutStr =+ "No entry: angleStep";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: angleStep";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		angleStep = stof(ValStr);
	}

	pElem = hParameters.FirstChild("treshold1").Element();
	if (!pElem)
	{
		OutStr = +"No entry: treshold1";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: treshold1";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		treshold1 = stof(ValStr);
	}

	pElem = hParameters.FirstChild("treshold2").Element();
	if (!pElem)
	{
		OutStr = +"No entry: treshold2";
		OutStr += "\n";
	}
	else if (!pElem->GetText())
	{
		OutStr = +"Empty entry: treshold2";
		OutStr += "\n";
	}
	else
	{
		ValStr = pElem->GetText();
		treshold2 = stof(ValStr);
	}

	cout << OutStr;
	return 1;
}
//--------------------------------------------------------------------------------------------------
string ProcessOptions::ShowParams(void)
{
	string OutString = "";
	OutString += "Input Directory 1:\t"		+ InFolderName1		+ "\n";
	OutString += "Input File Name Base 1:\t"	+ FileNameBase1		+ "\n";
	OutString += "File Name Extension 1:\t" + InFileExtension1	+ "\n";
	OutString += "Input File Name Base 1:\t"	+ InFilePattern1	+ "\n";

	OutString += "Input Directory 2:\t"		+ InFolderName2		+ "\n";
	OutString += "Input File Name Base 2:\t"	+ FileNameBase2		+ "\n";
	OutString += "File Name Extensiom 2:\t" + InFileExtension2	+ "\n";
	OutString += "Input File Name Pattern 2:\t"	+ InFilePattern2	+ "\n";

	OutString += "Input Directory 3:\t"		+ InFolderName3		+ "\n";
	OutString += "Input File Name Base 3:\t"	+ FileNameBase3		+ "\n";
	OutString += "File Name Extension 3:\t" + InFileExtension3	+ "\n";
	OutString += "Input File Name Pattern 3:\t"	+ InFilePattern3	+ "\n";

	OutString += "Input Directory 4:\t"		+ InFolderName4		+ "\n";
	OutString += "Input File Name Base 4:\t"	+ FileNameBase4		+ "\n";
	OutString += "File Name Extension 4:\t" + InFileExtension4	+ "\n";
	OutString += "Input File Name Pattern 4:\t"	+ InFilePattern4	+ "\n";

	OutString += "Input Directory 5:\t"		+ InFolderName5		+ "\n";
	OutString += "Input File Name Base 5:\t"	+ FileNameBase5		+ "\n";
	OutString += "File Name Extension 5:\t" + InFileExtension5	+ "\n";
	OutString += "Input File Name Pattern 5:\t"	+ InFilePattern5	+ "\n";

	OutString += "Input Directory 6:\t"		+ InFolderName6		+ "\n";
	OutString += "Input File Name Base 6:\t"	+ FileNameBase6		+ "\n";
	OutString += "File Name Extension 6:\t" + InFileExtension6	+ "\n";
	OutString += "Input File Name Base 6:\t"	+ InFilePattern6	+ "\n";

	OutString += "Output Directory:\t" + OutFolderName1 + "\n";
	OutString += "Output Directory 2:\t" + OutFolderName2 + "\n";
	
	OutString += "Preprocess Type:\t";
	OutString += to_string(preprocessType);
	OutString += " - ";
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

	OutString += "Display result:\t";
	if (displayResult)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Display small image:\t";
	if (displaySmallImage)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Tile Shape:\t";
	OutString += to_string(tileShape);
	OutString += " - ";
	switch (tileShape)
	{
	case 1:
		OutString += "Rectangular";
		break;
	case 2:
		OutString += "Elyptical";
		break;
	default:
		OutString += "none";
		break;
	}
	OutString += "\n";

	OutString += "Tile size x:\t";
	OutString += to_string(maxTileX);
	OutString += "\n";

	OutString += "Tile size y:\t";
	OutString += to_string(maxTileY);
	OutString += "\n";

	OutString += "Tile shift x:\t";
	OutString += to_string(shiftTileX);
	OutString += "\n";

	OutString += "Tile shift y:\t";
	OutString += to_string(shiftTileY);
	OutString += "\n";

	OutString += "Tile offset x:\t";
	OutString += to_string(offsetTileX);
	OutString += "\n";

	OutString += "Tile offset y:\t";
	OutString += to_string(offsetTileY);
	OutString += "\n";


	OutString += "Show tiles:\t";
	if (showTiles)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Tile Line Thickness>:\t";
	OutString += to_string(tileLineThickness);
	OutString += "\n";

	OutString += "Go thru:\t";
	if (goThru)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Use second image:\t";
	if (useSecondImage)
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

	OutString += "Normalisation:\t";
	OutString += to_string(normalisation);
	OutString += " - ";
	switch (tileShape)
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

	OutString += "Bin count:\t";
	OutString += to_string(binCount);
	OutString += "\n";

	OutString += "Min Ofset:\t";
	OutString += to_string(minOfset);
	OutString += "\n";

	OutString += "Max Ofset:\t";
	OutString += to_string(maxOfset);
	OutString += "\n";


	OutString += "Use Contrast:\t";
	if (useContrast)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Use Energy:\t";
	if (useEnergy)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Use Homogeneity:\t";
	if (useHomogeneity)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Use Correlation:\t";
	if (useCorrelation)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Min Hit:\t";
	OutString += to_string(minHit);
	OutString += "\n";

	OutString += "Use Min Mean:\t";
	if (useMinMean)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Min Mean:\t";
	OutString += to_string(minMean);
	OutString += "\n";

	OutString += "Min Norm:\t";
	OutString += to_string(minNorm);
	OutString += "\n";

	OutString += "Max Norm:\t";
	OutString += to_string(maxNorm);
	OutString += "\n";

	OutString += "Min Norm Global:\t";
	OutString += to_string(minNormGlobal);
	OutString += "\n";

	OutString += "Max Norm Global:\t";
	OutString += to_string(maxNormGlobal);
	OutString += "\n";

	OutString += "Use fixt display normalisation:\t";
	if (useFixtDispNorm)
		OutString += "Y";
	else
		OutString += "N";
	OutString += "\n";

	OutString += "Display Max:\t";
	OutString += to_string(displayMax);
	OutString += "\n";

	OutString += "Display Min:\t";
	OutString += to_string(displayMin);
	OutString += "\n";

	OutString += "Display Max2:\t";
	OutString += to_string(displayMax2);
	OutString += "\n";

	OutString += "Display Min2:\t";
	OutString += to_string(displayMin2);
	OutString += "\n";

	OutString += "Display Max3:\t";
	OutString += to_string(displayMax3);
	OutString += "\n";

	OutString += "Display Min3:\t";
	OutString += to_string(displayMin3);
	OutString += "\n";

	OutString += "Display Max4:\t";
	OutString += to_string(displayMax4);
	OutString += "\n";

	OutString += "Display Min4:\t";
	OutString += to_string(displayMin4);
	OutString += "\n";

	OutString += "Imposed Line Thickness>:\t";
	OutString += to_string(imposedLineThickness);
	OutString += "\n";

	OutString += "Line Half Length:\t";
	OutString += to_string(lineHalfLength);
	OutString += "\n";

	OutString += "Angle Step:\t";
	OutString += to_string(angleStep);
	OutString += "\n";

	OutString += "Interpolation:\t";
	OutString += to_string(interpolation);
	OutString += "\n";

	OutString += "treshold1:\t";
	OutString += to_string(treshold1);
	OutString += "\n";

	OutString += "treshold2:\t";
	OutString += to_string(treshold2);
	OutString += "\n";

	OutString += "\n";

	return OutString;
}