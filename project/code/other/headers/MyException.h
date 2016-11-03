#pragma once
#include <exception>

#include "../../view/headers/view.h"

class MyException : public std::exception
{
public:
	MyException();
	MyException(const char* const& errorText);
	MyException(const std::string errorText);
};



inline bool SwitchBetweenExceptionAndFalse(bool nothrow, std::string info)
{
	if (nothrow)
	{
		return false;
	}

	throw MyException(info);
}
