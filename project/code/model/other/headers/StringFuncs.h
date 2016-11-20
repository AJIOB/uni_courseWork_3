#pragma once
#include <string>
#include <vector>

#include "../../../model/exceptions/AllExceptions.h"
//#include "ISBNOnePart.h"

namespace AJIOBStringFuncs
{
	std::string StringCat(const std::string& str, const int i);
	std::string IntToString(const long int& num);
	long int StringToInt(const std::string& text);

	void Invert(std::string& str);

	std::vector<std::string> BreakStringToArrayOfStrings(const std::string& str, const char devider = ' ');
	void BreakStringTo2Strings(const std::string str, std::string& leftResult, std::string& rightResult, const char devider = ' ');
}
