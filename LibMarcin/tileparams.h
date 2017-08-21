#ifndef TILEPARAMS_H
#define TILEPARAMS_H

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

class TileParams
{
public:
    int tileY;
    int tileX;
    int paramsCount;
    std::vector<float>Params;

    TileParams();
    ~TileParams();
    void FromString(std::string);
};


class FileParams
{
public:
    boost::filesystem::path ImFileName;
    int tileShape;
    int maxTileX;
    int maxTileY;
    int shiftTileX;
    int shiftTileY;
    int offsetTileX;
    int offsetTileY;
    int ValueCount;
    std::vector<std::string> NamesVector;
    std::vector<TileParams> ParamsVect;

    FileParams();
    ~FileParams();

};

#endif // TILEPARAMS_H
