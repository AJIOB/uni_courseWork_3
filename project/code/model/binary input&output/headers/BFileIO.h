#pragma once

#include <string>
#include <fstream>
//#include <iostream>

//#include "log.h"
//#include "../../../other/headers/MyException.h"
#include "../../../model/exceptions/AllExceptions.h"
#include "../../../view/headers/view.h"
//#include "BStringIO.h"
/*
//Мои константы
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
	//файловый поток (наш файл)
	std::ofstream fout;
	std::ifstream fin;
	//путь к файлу с его именем
	std::string cl_fileName;
	
	//методы для открытия/закрытия файла
	bool FileOpenIn();
	bool FileOpenOut();
	bool FileReset(bool nothrow = false);
	void FileClose();
	
	std::string ReadStringFromFile();
	
	bool WriteStringToFile(const std::string& info);

public:
	AJIOB_BinaryFileInputOutput(const std::string& fileName);
	virtual ~AJIOB_BinaryFileInputOutput();

	std::string GetFileName() const;
};
