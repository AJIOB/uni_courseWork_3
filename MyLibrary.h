#pragma once

//��� .cpp � �� ������
#include <iostream>
//#include <conio.h>
//#include <vector>

#include "authClass.h"
#include "log.h"
#include "AJIOBMenuClass.h"

//�������� �������
inline void programBegin()
{
	std::cout <<  "������������! �� ��������� ��������� \"����������\"" << std::endl << "��������� �����������, ����������, ���������..." << std::endl;
	AJIOB_ProgramLog("�������� ���������");
}

int defaultFunction();

//����� ���������
inline void programEnd()
{
	std::cout << "��������� ��������� ���� ������. ��� ������ ������� ����� ������" << std::endl;
	AJIOB_ProgramLog("���������� ���������", true);
	fflush(stdin);
	std::cin.get();
}
