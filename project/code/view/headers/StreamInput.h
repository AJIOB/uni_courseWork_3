#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../../other/headers/MyException.h"
#include "StreamOutput.h"

inline void ClearStream()
{
	std::cin.clear();

	while (std::cin.get()!='\n');
}

template<typename InputType>
InputType Input()
{
	InputType toReturn;
	std::cin >> toReturn;
	ClearStream();
	/*
	while (true)
	{
		if (!(std::cin >> toReturn))
		{
			
		}
		ClearStream();
	}*/
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

inline int InputEnum(const std::vector<std::string>& texts, int numOfTheFirstElementToShow = 1)
{
	int result = 0;

	while (true)
	{
		std::cout << "Пожалуйста, введите цифру, соответсувующую вашему выбору:" << std::endl;
		for (auto i = numOfTheFirstElementToShow; i < texts.size(); ++i)
		{
			std::cout << i << ": " << texts[i] << std::endl;
		}

		OutputInfo("Пожалуйста, сделайте свой выбор:");

		if ((std::cin >> result) && (result >= numOfTheFirstElementToShow) && (result < texts.size()))
		{
			ClearStream();
			break;
		}		

		ClearStream();
		system("cls");

		OutputWarning("Извините, такой вариант нельзя ввести. Пожалуйста, введите что-либо из вышепредложенных вариантов");
	}

	return result;
}