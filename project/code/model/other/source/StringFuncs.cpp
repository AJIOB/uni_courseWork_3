#include "../headers/StringFuncs.h"

#define N 15

std::string StringCat(const std::string& str, const int i)
{
	std::string toReturn(str);
	char buf[N] = "";
	toReturn += _itoa_s(i, buf, N, 10);
	return toReturn;
}

#undef N