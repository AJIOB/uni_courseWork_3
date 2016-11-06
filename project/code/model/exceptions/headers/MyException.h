#pragma once
#include <exception>
#include <string>

//#include "../../view/headers/view.h"

#ifndef STREAM_IO
void OutputLog(const std::string&, bool);
//void OutputLog(const std::string&);
#endif

class MyException : public std::exception
{
public:
	MyException();
	MyException(const char* const& errorText);
	MyException(const std::string errorText);
};



inline bool SwitchBetweenExceptionAndFalse(bool nothrow, const std::string& info)
{
	if (nothrow)
	{
		return false;
	}

	throw MyException(info);
}
