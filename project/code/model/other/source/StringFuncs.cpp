#include "../headers/StringFuncs.h"

#define N 15

std::string StringCat(const std::string& str, const int i)
{
	char buf[N] = "";
	if (auto err = _itoa_s(i, buf, N, 10))
	{
		throw MyException(std::string("Can't convert int to string"));
	}
	return (str + buf);
}

#undef N