#include <windows.h>

#include "headers/MyLibrary.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	programBegin();
	
	int errorCode = defaultFunction();
	
	programEnd();
	return errorCode;
}