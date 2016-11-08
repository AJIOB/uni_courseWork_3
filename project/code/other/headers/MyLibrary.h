#pragma once

//для .cpp и не только
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "../../controller/headers/AJIOBMenuClass.h"
#include "../../controller/headers/authClass.h"
#include "../../model/exceptions/AllExceptions.h"

//основная функция
inline void programBegin()
{
	OutputConsole("Здравствуйте! Вы запустили программу \"Библиотека\"");
	OutputConsole("Программа загружается, пожалуйста, подождите...");
	OutputLog("Загрузка программы");
}

int defaultFunction();

//конец программы
inline void programEnd()
{
	OutputConsole("Программа завершила свою работу. Для выхода введите любой символ");
	OutputLog("Завершение программы", true);
	Stream::Get();
	//fflush(stdin);
	//std::cin.get();
}
