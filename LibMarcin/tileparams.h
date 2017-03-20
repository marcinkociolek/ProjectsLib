#ifndef TILEPARAMS_H
#define TILEPARAMS_H

#include <iostream>
#include <vector>
class TileParams
{
public:
    int tileY;
    int tileX;
    int paramsCount;
    //double *Params;
    std::vector<double> Params;
    TileParams();
    void FromString(std::string);
};

#endif // TILEPARAMS_H
