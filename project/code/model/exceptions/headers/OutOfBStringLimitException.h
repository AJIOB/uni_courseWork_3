#pragma once
#include "MyException.h"

class OutOfBStringLimitException : public MyException
{
public:
	OutOfBStringLimitException();
};

inline OutOfBStringLimitException::OutOfBStringLimitException() : MyException("Выход за пределы бинарной строки")
{

}
