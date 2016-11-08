#include "../headers/StreamInput.h"

char Stream::GetOnlyYN(const std::string& infoText)
{
	char result;

	while (true)
	{
		OutputConsole(infoText +  " (Y - ��, N - ���)");
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

		OutputConsole("��������, ����� ������� �� ��������������. ����������, ��������� ����");
	}

	return result;
}

int Stream::InputEnum(const std::vector<std::string>& texts, int numOfTheFirstElementToShow)
{
	int result = 0;

	while (true)
	{
		std::cout << "����������, ������� �����, ��������������� ������ ������:" << std::endl;
		for (long int i = numOfTheFirstElementToShow; i < static_cast<long int>(texts.size()); ++i)
		{
			std::cout << i << ": " << texts[i] << std::endl;
		}

		OutputConsole("����������, �������� ���� �����:");

		if ((std::cin >> result) && (result >= numOfTheFirstElementToShow) && (result < static_cast<long int>(texts.size())))
		{
			Clear();
			break;
		}		

		Clear();
		ClearConsole();

		OutputWarning("��������, ����� ������� ������ ������. ����������, ������� ���-���� �� ���������������� ���������");
	}

	return result;
}