#include "StringFcLib.h"
#include <iostream>

using namespace std;
string ItoStrLZ(int nr, int leadZerosCount)
{
	if (leadZerosCount > 10)
		return "to much zeros";
	
	int divisor = 1;
	for (int i = 2; i <= leadZerosCount; i++)
		divisor *= 10;

	if (nr > divisor * 10)
		return "to big nr";

	char Buf[12];
	int iBuf = 0;
	if (nr < 0)
	{
		Buf[iBuf] = '-';
		iBuf++;
        nr = nr * -1;
	}


	for (int i = 0; i < leadZerosCount; i++)
	{
		int leter = nr / divisor;
		int rest = nr % divisor;
		if ((leter <= 9) | (leter >= 0))
			Buf[iBuf] = '0' + (char)(leter);
		else
			Buf[iBuf] = '^';
		iBuf++;
		nr = rest;
        divisor /= 10;
	}
	Buf[iBuf] = 0;
	return Buf;
}

//----------------------------------------------------------------------------------------------------------------------------------
string ItoStrLZPlusSign(int nr, int leadZerosCount)
{
    if (leadZerosCount > 10)
        return "to much zeros";

    int divisor = 1;
    for (int i = 2; i <= leadZerosCount; i++)
        divisor *= 10;

    if (nr > divisor * 10)
        return "to big nr";

    char Buf[12];
    int iBuf = 0;
    if (nr < 0)
    {
        nr *= -1;
        Buf[iBuf] = '-';
        iBuf++;
    }
    else
    {
        Buf[iBuf] = '+';
        iBuf++;
    }

    for (int i = 0; i < leadZerosCount; i++)
    {
        int leter = nr / divisor;
        int rest = nr % divisor;
        if ((leter <= 9) | (leter >= 0))
            Buf[iBuf] = '0' + (char)(leter);
        else
            Buf[iBuf] = '^';
        iBuf++;
        nr = rest;
        divisor /= 10;
    }
    Buf[iBuf] = 0;
    return Buf;
}


string ItoStrLS(int nr, int leadSpaceCount)
{
	if (leadSpaceCount > 10)
		return "to much zeros";

	int divisor = 1;
	for (int i = 2; i <= leadSpaceCount; i++)
		divisor *= 10;

	if (nr > divisor * 10)
		return "to big nr";

	char Buf[12];
	int iBuf = 0;
	if (nr < 0)
	{
		Buf[iBuf] = '-';
		iBuf++;
	}


	for (int i = 0; i < leadSpaceCount; i++)
	{
		int leter = nr / divisor;
		int rest = nr % divisor;
		if ((leter <= 9) | (leter >= 0))
			Buf[iBuf] = '0' + (char)(leter);
		else
			Buf[iBuf] = '^';
		iBuf++;
		nr = rest;
		divisor /= 10;
	}
	Buf[iBuf] = 0;
	return Buf;
}
//----------------------------------------------------------------------------------------------------------------------------------
QString ItoQStrLZ(int nr, int leadZerosCount)
{
    if (leadZerosCount > 10)
        return "to much zeros";

    int divisor = 1;
    for (int i = 2; i <= leadZerosCount; i++)
        divisor *= 10;

    if (nr > divisor * 10)
        return "to big nr";

    char Buf[12];
    int iBuf = 0;
    if (nr < 0)
    {
        Buf[iBuf] = '-';
        iBuf++;
        nr = nr * -1;
    }


    for (int i = 0; i < leadZerosCount; i++)
    {
        int leter = nr / divisor;
        int rest = nr % divisor;
        if ((leter <= 9) | (leter >= 0))
            Buf[iBuf] = '0' + (char)(leter);
        else
            Buf[iBuf] = '^';
        iBuf++;
        nr = rest;
        divisor /= 10;
    }
    Buf[iBuf] = 0;
    return Buf;
}

