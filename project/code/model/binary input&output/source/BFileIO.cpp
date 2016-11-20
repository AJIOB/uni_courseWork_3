#include "../headers/BFileIO.h"


//Co-/destructors
AJIOB_BinaryFileInputOutput::AJIOB_BinaryFileInputOutput(const std::string& fileName)
{
	cl_fileName = fileName;
}

AJIOB_BinaryFileInputOutput::~AJIOB_BinaryFileInputOutput()
{
	cl_fileName.clear();
	FileClose();
}

std::string AJIOB_BinaryFileInputOutput::GetFileName() const
{
	return cl_fileName;
}

bool AJIOB_BinaryFileInputOutput::FileOpenIn()
{
	FileClose();

	try
	{
		fin.open(cl_fileName, std::ios::binary | std::ios::in);
		if (!fin.is_open())
		{
			OutputLog("Не удается открыть файл " + cl_fileName + " для чтения");
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		OutputLog("Не удается открыть файл " + cl_fileName + " для чтения. Ошибка: " + e.what());
		return false;
	}

	return true;
}


// open/close file
bool AJIOB_BinaryFileInputOutput::FileOpenOut()
{
	FileClose();

	try
	{
		fout.open(cl_fileName, std::ios::binary | std::ios::out | std::ios::app);
		if (!fout.is_open())
		{
			OutputLog("Не удается открыть файл " + cl_fileName + " для записи");
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		OutputLog("Не удается открыть файл " + cl_fileName + " для записи. Ошибка: " + e.what());
		return false;
	}

	return true;
}

bool AJIOB_BinaryFileInputOutput::FileReset(bool nothrow)
{
	FileClose();

	try
	{
		fout.open(cl_fileName, std::ios::binary | std::ios::out | /*std::ios::app |*/ std::ios::trunc);
		if (!fout.is_open())
		{
			SwitchBetweenExceptionAndFalse(nothrow, "Не удается сбросить файл " + cl_fileName);
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		SwitchBetweenExceptionAndFalse(nothrow, "Не удается сбросить файл " + cl_fileName + ". Ошибка: " + e.what());
		return false;
	}

	return true;
}

void AJIOB_BinaryFileInputOutput::FileClose()
{
	if (fout.is_open())
	{
		fout.close();
	}

	if (fin.is_open())
	{
		fin.close();
	}
}


//IO
std::string AJIOB_BinaryFileInputOutput::ReadStringFromFile()
{
	if (!fin.is_open() || fin.eof())
	{
		throw FReadException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". Файл не открыт или уже закончился");
	}

	size_t len = readSize_tFromFile();

	/*
	if (len == badInt || len < 0)
	{
		throw MyException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". В файле некорректная длина строки");
	}
	*/

	//строка пуста => вернем пустую строку
	if (len == 0)
	{
		return std::string();
	}

	char* tmp = new (std::nothrow) char[len];
	if (!tmp)
	{
		throw MyException("No memory to allocate temporary char array in method ReadStringFromFile()");
	}

	//читаем саму строку
	fin.read(tmp, len);
	
	if (fin.eof())
	{
		delete [] tmp;
		throw FReadException("Имя файла: " + std::string(cl_fileName) + ". Файл закончился");
	}

	std::string for_return(tmp, len);
	delete [] tmp;

	return for_return;
}

size_t AJIOB_BinaryFileInputOutput::readSize_tFromFile()
{
	if (!fin.is_open() || fin.eof())
	{
		throw FReadException("Имя файла: " + std::string(cl_fileName) + ". Файл не открыт или уже закончился");
	}

	//читаем сам size_t
	size_t tmp;
	fin.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
	
	if (fin.eof())
	{
		throw FReadException("Имя файла: " + std::string(cl_fileName) + ". Файл закончился");
	}

	return tmp;
}

bool AJIOB_BinaryFileInputOutput::WriteStringToFile(const std::string& info)
{
	if (!fout.is_open() || !writeSize_tToFile(info.length()))
	{
		return false;
	}

	fout.write(info.c_str(), info.length());

	return true;
}

bool AJIOB_BinaryFileInputOutput::writeSize_tToFile(const size_t& info)
{
	if (!fout.is_open())
	{
		return false;
	}

	fout.write(reinterpret_cast<const char *>(&info), sizeof info);
	
	return true;
}