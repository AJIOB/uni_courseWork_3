﻿#pragma once
#include <string>

#include "../../../model/exceptions/AllExceptions.h"
#include "ISBNOnePart.h"

namespace AJIOBStringFuncs
{
	std::string StringCat(const std::string& str, const int i);
	std::string IntToString(const long int& num);
	long int StringToInt(const std::string& text);

	void Invert(std::string& str);
}
