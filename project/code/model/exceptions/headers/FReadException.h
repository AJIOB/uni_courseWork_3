#pragma once
#include "MyException.h"

class FReadException : public MyException
{
public:
	FReadException(const std::string str = "");
};

inline FReadException::FReadException(const std::string str) : MyException("Ошибка чтения из файла. " + str)
{

}
