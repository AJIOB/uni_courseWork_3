#pragma once

//��� .cpp � �� ������
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "../../controller/headers/AJIOBMenuClass.h"
#include "../../controller/headers/authClass.h"
#include "../../model/exceptions/AllExceptions.h"

//�������� �������
inline void programBegin()
{
	OutputConsole("������������! �� ��������� ��������� \"����������\"");
	OutputConsole("��������� �����������, ����������, ���������...");
	OutputLog("�������� ���������");
}

int defaultFunction();

//����� ���������
inline void programEnd()
{
	OutputConsole("��������� ��������� ���� ������. ��� ������ ������� ����� ������");
	OutputLog("���������� ���������", true);
	Stream::Get();
	//fflush(stdin);
	//std::cin.get();
}
