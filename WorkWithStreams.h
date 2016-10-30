#pragma once
#include <iostream>
#include <string>

#include "MyException.h"

inline void ClearStream()
{
	std::cin.clear();

	while (std::cin.get()!='\n');
}

inline bool SwitchBetweenExceptionAndFalse(bool nothrow, std::string info)
{
	if (nothrow)
	{
		return false;
	}

	throw MyException(info);
}

inline char Get()
{
	char toReturn = std::cin.get();
	ClearStream();
	return toReturn;
}

template<typename InputType>
InputType Input()
{
	InputType toReturn;
	std::cin >> toReturn;
	ClearStream();
	return toReturn;
}
