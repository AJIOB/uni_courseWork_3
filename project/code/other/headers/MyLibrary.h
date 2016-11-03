#pragma once

//для .cpp и не только
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "../../controller/headers/AJIOBMenuClass.h"
#include "../../controller/headers/authClass.h"

//основная функция
inline void programBegin()
{
	OutputInfo("Здравствуйте! Вы запустили программу \"Библиотека\"");
	OutputInfo("Программа загружается, пожалуйста, подождите...");
	OutputLog("Загрузка программы");
}

int defaultFunction();

//конец программы
inline void programEnd()
{
	OutputInfo("Программа завершила свою работу. Для выхода введите любой символ");
	OutputLog("Завершение программы", true);
	fflush(stdin);
	std::cin.get();
}
