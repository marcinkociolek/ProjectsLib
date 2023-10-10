#ifndef StringFcLib
#define StringFcLib
//--------------------------------------------------------------------------------------------
//#include <stdio.h>
#include <iostream>
#include <QString>

std::string ItoStrLZ(int nr, int leadZerosCount);
std::string ItoStrLZPlusSign(int nr, int leadZerosCount);
std::string ItoStrLS(int nr, int leadSpaceCount);

QString ItoQStrLZ(int nr, int leadZerosCount);

#endif
