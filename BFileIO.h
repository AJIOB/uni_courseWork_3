#pragma once

#include <string>
#include <fstream>
//#include <iostream>

#include "log.h"
#include "MyException.h"
//#include "BStringIO.h"
/*
//��� ���������
static const int badInt = -23;
static const double badDouble = -89.34;
static const std::string badString("empty");
*/
/*	
 *	Basic binary input/output in file
 *	
 **/
class AJIOB_BinaryFileInputOutput/* : private BStringIO**/
{
	//File IO help
	
	size_t readSize_tFromFile();
	bool writeSize_tToFile(const size_t& info);

protected:
	//�������� ����� (��� ����)
	std::ofstream fout;
	std::ifstream fin;
	//���� � ����� � ��� ������
	std::string cl_fileName;
	//�������, � ������� ������
	//int cl_inputPos;

	//������ ��� ��������/�������� �����
	bool FileOpenIn();
	bool FileOpenOut();
	bool FileReset();
	void FileClose();
	//�������� public
//public:
	std::string ReadStringFromFile();
	/*
	int readIntFromFile();
	double readDoubleFromFile();
*/
	bool WriteStringToFile(const std::string& info);/*
	bool writeIntToFile(const int& info);
	bool writeDoubleToFile(const double& info);
	*/
public:
	AJIOB_BinaryFileInputOutput(const std::string& fileName);
	~AJIOB_BinaryFileInputOutput();
};