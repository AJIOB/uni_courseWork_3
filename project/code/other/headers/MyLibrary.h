#pragma once

//��� .cpp � �� ������
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "../../controller/headers/AJIOBMenuClass.h"
#include "../../controller/headers/authClass.h"
#include "NoLoginException.h"

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
	Get();
	//fflush(stdin);
	//std::cin.get();
}
