#include "../headers/MyLibrary.h"

//#include "ExternalLib.h"


int defaultFunction()
{
	int errorCode = 0;

	try
	{
		AJIOBMenuClass localMenu;
		errorCode = localMenu.run();
	}
	catch (...)
	{
		OutputConsole("У нас какая-то ошибка");
		errorCode = -1;
	}

	return errorCode;
}
