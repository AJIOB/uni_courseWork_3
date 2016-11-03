#include "../headers/log.h"

void AJIOB::ProgramLog(const std::string putToLogFile, const bool isCloseFile)
{
	//Чтобы переменная с открытым файлом всегда была видна
	static std::ofstream file;

	if (!file.is_open())
	{
		file.open(logfileWay, std::ios::out | std::ios::app);

		if (!file.is_open())
		{
			std::cout << errorText << std::endl;
			return;
		}
	}

	time_t currentTime;

	//получает текущее время
	time(&currentTime);
	//преобразовывет его в строку
	char timeInChar[strSize];

	ctime_s(timeInChar, strSize, &currentTime);
	//убираем \n в конце строки
	timeInChar [strlen(timeInChar) - 1] = '\0';

	file << timeInChar << ": " << putToLogFile << std::endl;

	if (isCloseFile)
	{
		file.close();
	}
}
