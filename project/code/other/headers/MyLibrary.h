#pragma once

//��� .cpp � �� ������
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "../../controller/headers/AJIOBMenuClass.h"
#include "../../controller/headers/authClass.h"

//�������� �������
inline void programBegin()
{
	OutputInfo("������������! �� ��������� ��������� \"����������\"");
	OutputInfo("��������� �����������, ����������, ���������...");
	OutputLog("�������� ���������");
}

int defaultFunction();

//����� ���������
inline void programEnd()
{
	OutputInfo("��������� ��������� ���� ������. ��� ������ ������� ����� ������");
	OutputLog("���������� ���������", true);
	fflush(stdin);
	std::cin.get();
}
