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
			OutputLog("�� ������� ������� ���� " + cl_fileName + " ��� ������");
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		OutputLog("�� ������� ������� ���� " + cl_fileName + " ��� ������. ������: " + e.what());
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
			OutputLog("�� ������� ������� ���� " + cl_fileName + " ��� ������");
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		OutputLog("�� ������� ������� ���� " + cl_fileName + " ��� ������. ������: " + e.what());
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
			SwitchBetweenExceptionAndFalse(nothrow, "�� ������� �������� ���� " + cl_fileName);
			return false;
		}
	}
	catch (std::ios_base::failure e)
	{
		SwitchBetweenExceptionAndFalse(nothrow, "�� ������� �������� ���� " + cl_fileName + ". ������: " + e.what());
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
		throw FReadException("������ ������ ������ �� ����� " + std::string(cl_fileName) + ". ���� �� ������ ��� ��� ����������");
	}

	size_t len = readSize_tFromFile();

	/*
	if (len == badInt || len < 0)
	{
		throw MyException("������ ������ ������ �� ����� " + std::string(cl_fileName) + ". � ����� ������������ ����� ������");
	}
	*/

	//������ ����� => ������ ������ ������
	if (len == 0)
	{
		return std::string();
	}

	char* tmp = new (std::nothrow) char[len];
	if (!tmp)
	{
		throw MyException("No memory to allocate temporary char array in method ReadStringFromFile()");
	}

	//������ ���� ������
	fin.read(tmp, len);
	
	if (fin.eof())
	{
		delete [] tmp;
		throw FReadException("��� �����: " + std::string(cl_fileName) + ". ���� ����������");
	}

	std::string for_return(tmp, len);
	delete [] tmp;

	return for_return;
}

size_t AJIOB_BinaryFileInputOutput::readSize_tFromFile()
{
	if (!fin.is_open() || fin.eof())
	{
		throw FReadException("��� �����: " + std::string(cl_fileName) + ". ���� �� ������ ��� ��� ����������");
	}

	//������ ��� size_t
	size_t tmp;
	fin.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
	
	if (fin.eof())
	{
		throw FReadException("��� �����: " + std::string(cl_fileName) + ". ���� ����������");
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