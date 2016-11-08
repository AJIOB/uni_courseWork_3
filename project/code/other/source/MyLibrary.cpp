#include "../headers/MyLibrary.h"

int defaultFunction()
{
	int errorCode = 0;
	/*
	 *������������� � ������������� Control+C �������*/
	/*if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE ) ) 
	{
		errorCode = 2;
		OutputConsole("�� ������� ��������� ���������. ��� ������: 2. �������...");
		OutputLog("�� ������� ��������� ���������. ��� ������: 2. �������...");
		return errorCode;
	}*/

	try
	{
		AJIOBMenuClass localMenu;
		errorCode = localMenu.run();
	}
	catch (...)
	{
		OutputConsole("� ��� �����-�� ������");
		errorCode = 1;
	}

	return errorCode;
}
