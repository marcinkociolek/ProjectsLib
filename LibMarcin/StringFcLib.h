#ifndef StringFcLib
#define StringFcLib
//--------------------------------------------------------------------------------------------
//#include <stdio.h>
#include <iostream>

std::string ItoStrLZ(int nr, int leadZerosCount);
std::string ItoStrLZPlusSign(int nr, int leadZerosCount);
std::string ItoStrLS(int nr, int leadSpaceCount);

#endif
