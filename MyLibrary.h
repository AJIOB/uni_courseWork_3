#pragma once

//��� .cpp � �� ������
#include <iostream>
#include <conio.h>
//#include <vector>

#include "authClass.h"
#include "log.h"

//�������� �������
inline void programBegin()
{
	std::cout <<  "������������! �� ��������� ��������� \"����������\"" << std::endl << "��������� �����������, ����������, ���������" << std::endl;
	AJIOB_ProgramLog("�������� ���������");
}

void defaultFunction();

//����� ���������
inline void programEnd()
{
	std::cout << "��������� ��������� ���� ������. ��� ������ ������� ����� ������" << std::endl;
	AJIOB_ProgramLog("���������� ���������", "Error when open log file",true);
	fflush(stdin);
	std::cin.get();
}
