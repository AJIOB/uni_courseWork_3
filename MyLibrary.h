#pragma once

//для .cpp и не только
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "authClass.h"
#include "log.h"
#include "AJIOBMenuClass.h"

//основная функция
inline void programBegin()
{
	std::cout <<  "Здравствуйте! Вы запустили программу \"Библиотека\"" << std::endl << "Программа загружается, пожалуйста, подождите..." << std::endl;
	AJIOB_ProgramLog("Загрузка программы");
}

int defaultFunction();

//конец программы
inline void programEnd()
{
	std::cout << "Программа завершила свою работу. Для выхода введите любой символ" << std::endl;
	AJIOB_ProgramLog("Завершение программы", true);
	fflush(stdin);
	std::cin.get();
}
