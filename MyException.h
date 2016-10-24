#pragma once
#include <exception>

#include "log.h"

class MyException : std::exception
{
public:
	MyException();
	MyException(const char* const& errorText);
	MyException(const std::string errorText);
};
