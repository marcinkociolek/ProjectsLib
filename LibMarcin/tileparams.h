#ifndef TILEPARAMS_H
#define TILEPARAMS_H

#include <iostream>

class TileParams
{
public:
    int tileY;
    int tileX;
    int paramsCount;
    float *Params;
    TileParams();
    void FromString(std::string);
};

#endif // TILEPARAMS_H
