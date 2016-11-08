#include "../headers/StreamInput.h"

char Stream::GetOnlyYN(const std::string& infoText)
{
	char result;

	while (true)
	{
		OutputConsole(infoText +  " (Y - да, N - нет)");
		result = Stream::Get();

		if (result == 'y' || (result == 'n'))
		{
			result += 'A' - 'a';
			break;
		}

		if (result == 'Y' || (result == 'N'))
		{
			break;
		}

		OutputConsole("Извините, такой вариант не поддерживается. Пожалуйста, повторите ввод");
	}

	return result;
}

int Stream::InputEnum(const std::vector<std::string>& texts, int numOfTheFirstElementToShow)
{
	int result = 0;

	while (true)
	{
		std::cout << "Пожалуйста, введите цифру, соответсувующую вашему выбору:" << std::endl;
		for (long int i = numOfTheFirstElementToShow; i < static_cast<long int>(texts.size()); ++i)
		{
			std::cout << i << ": " << texts[i] << std::endl;
		}

		OutputConsole("Пожалуйста, сделайте свой выбор:");

		if ((std::cin >> result) && (result >= numOfTheFirstElementToShow) && (result < static_cast<long int>(texts.size())))
		{
			Clear();
			break;
		}		

		Clear();
		ClearConsole();

		OutputWarning("Извините, такой вариант нельзя ввести. Пожалуйста, введите что-либо из нижепредложенных вариантов");
	}

	return result;
}