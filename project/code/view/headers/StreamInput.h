#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "StreamOutput.h"
//#include "../../other/headers/MyException.h"
#include "../../model/exceptions/AllExceptions.h"

namespace Stream
{
	inline void Clear()
	{
		std::cin.clear();
		std::cin.good();

		if (std::cin.peek() == std::char_traits<char>::eof())
		{
			return;
		}

		while (std::cin.get() != '\n');
	}

	template<typename InputType>
	InputType Input()
	{
		InputType toReturn;

		while (true)
		{
			if (std::cin >> toReturn)
			{
				Clear();
				break;
			}
			OutputConsole("Ошибка ввода. Пожалуйста, повторите ввод");
			Clear();
		}
		return toReturn;
	}

	template<typename InputType>
	void Input(InputType& elem)
	{
		InputType buffer;

		while (true)
		{
			if (std::cin >> buffer)
			{
				Clear();
				break;
			}

			Clear();
			OutputConsole("Ошибка ввода. Пожалуйста, повторите ввод");
		}

		elem = buffer;
	}

	inline char Get()
	{
		/*
		char toReturn = std::cin.get();
		Clear();
		return toReturn;*/

		return Input<char>();
	}


	char GetOnlyYN(const std::string& infoText);

	int InputEnum(const std::vector<std::string>& texts, int numOfTheFirstElementToShow = 1);

	//class MinMaxException;

	template<typename InputType>
	InputType InputInRange(const std::string& shownText, const InputType& min, const InputType& max)
	{
		if (min > max)
		{
			//throw MinMaxException();
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
}