#pragma once

#include "MyException.h"

class NoLoginException : public MyException
{
public:
	NoLoginException();
};

inline NoLoginException::NoLoginException() : MyException("Авторизация не удалась")
{
}
