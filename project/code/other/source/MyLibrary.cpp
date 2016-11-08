#include "../headers/MyLibrary.h"

int defaultFunction()
{
	int errorCode = 0;
	/*
	 *доразобраться с отлавливанием Control+C нажатий*/
	/*if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE ) ) 
	{
		errorCode = 2;
		OutputConsole("Не удалось загрузить программу. Код ошибки: 2. Выходим...");
		OutputLog("Не удалось загрузить программу. Код ошибки: 2. Выходим...");
		return errorCode;
	}*/

	try
	{
		AJIOBMenuClass localMenu;
		errorCode = localMenu.run();
	}
	catch (...)
	{
		OutputConsole("У нас какая-то ошибка");
		errorCode = 1;
	}

	return errorCode;
}
