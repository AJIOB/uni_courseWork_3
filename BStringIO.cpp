#include "BStringIO.h"
/*
//read methods

size_t BStringIO::readSize_t(const std::string& str, strPos& iterator)
{
	if (iterator >= str.length() || ((iterator + sizeof size_t) < 1))
	{
		throw MyException("Ошибка чтения из бинарной строки. Выход за границы.");
	}

	//читаем сам size_t
	size_t tmp;
	fin.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
	
	if (fin.eof())
	{
		throw MyException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". Файл закончился");
	}

	return tmp;
}

int BStringIO::readInt()
{
	if (!fin.is_open() || fin.eof())
	{
		//return badInt;
		throw MyException();
	}

	//читаем сам int
	int tmp;
	fin.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
	
	if (fin.eof())
	{
		return badInt;
	}

	return tmp;
}

double BStringIO::readDouble()
{
	if (!fin.is_open() || fin.eof())
	{
		return badDouble;
	}

	//читаем сам double
	double tmp;
	fin.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
	
	if (fin.eof())
	{
		return badDouble;
	}

	return tmp;
}

bool BStringIO::writeInt(const int& info)
{
	if (!fout.is_open())
	{
		return false;
	}

	fout.write(reinterpret_cast<const char *>(&info), sizeof info);
	
	return true;
}

bool BStringIO::writeDouble(const double& info)
{
	if (!fout.is_open())
	{
		return false;
	}

	fout.write(reinterpret_cast<const char *>(&info), sizeof info);
	
	return true;
}

std::string BStringIO::readString()
{
	if (!fin.is_open() || fin.eof())
	{
		throw MyException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". Файл не открыт или уже закончился");
	}

	size_t len = readSize_t();

	/*
	if (len == badInt || len < 0)
	{
		throw MyException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". В файле некорректная длина строки");
	}
	*/
/*
	//строка пуста => вернем пустую строку
	if (len == 0)
	{
		return std::string();
	}

	char* tmp = new (std::nothrow) char[len];
	if (!tmp)
	{
		throw MyException("No memory to allocate temporary char array in method readString()");
	}

	//читаем саму строку
	fin.read(tmp, len);
	
	if (fin.eof())
	{
		delete [] tmp;
		throw MyException("Ошибка чтения строки из файла " + std::string(cl_fileName) + ". Файл закончился");
	}

	std::string for_return(tmp, len);
	delete [] tmp;

	return for_return;
}

bool BStringIO::writeString(const std::string& info)
{
	if (!fout.is_open() || !writeSize_t(info.length()))
	{
		return false;
	}

	const char* tmpCString = info.c_str();
	fout.write(tmpCString, info.length());
	delete [] tmpCString;

	return true;
}

bool BStringIO::writeSize_t(const size_t& info)
{
	if (!fout.is_open())
	{
		return false;
	}

	fout.write(reinterpret_cast<const char *>(&info), sizeof info);
	
	return true;
}*/