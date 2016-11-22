#pragma once

#include "MyException.h"

class RepeatException : public MyException
{
public:
	RepeatException();
};

inline RepeatException::RepeatException() : MyException("Пользователь пожелал отменить ввод при введении повтора")
{
}
