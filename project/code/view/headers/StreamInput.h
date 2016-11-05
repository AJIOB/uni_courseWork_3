#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../../other/headers/MyException.h"
#include "StreamOutput.h"

inline void ClearStream()
{
	std::cin.clear();
	std::cin.good();

	while ((std::cin.get())!='\n');
}

template<typename InputType>
InputType Input()
{
	InputType toReturn;

	while (true)
	{
		if (std::cin >> toReturn)
		{
			ClearStream();
			break;
		}
		OutputConsole("Ошибка ввода. Пожалуйста, повторите ввод");
		ClearStream();
	}
	return toReturn;
}

inline char Get()
{
	/*
	char toReturn = std::cin.get();
	ClearStream();
	return toReturn;*/

	return Input<char>();
}


char GetOnlyYN(const std::string& infoText);

int InputEnum(const std::vector<std::string>& texts, int numOfTheFirstElementToShow = 1);

template<typename InputType>
InputType InputInRange(const std::string& shownText, const InputType& min, const InputType& max)
{
	if (min > max)
	{
		//throw;
	}

	InputType buffer;
	while (true)
	{
		OutputConsole(shownText);
		buffer = Input<InputType>();
		if ((buffer >= min) && (buffer <= max))
		{
			break;
		}

		std::cout << "Извините, такого элемента нету. Пожалуйста, введите элемент из промежутка от " << min << " до " << max << std::endl;
		PauseConsole();
		ClearConsole();
	}

	return buffer;
}