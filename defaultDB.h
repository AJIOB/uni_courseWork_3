#pragma once

#include <vector>

#include "BFileIO.h"
#include "BStringIO.h"

#include "WorkWithStreams.h"

template <typename oneElementOfDB>
class DefaultDB : public AJIOB_BinaryFileInputOutput
{
	//����
	std::vector<oneElementOfDB> cl_ourArray;

	//���� ���������
	bool cl_isChanged;

public:
	DefaultDB(const std::string& wayToFile);
	~DefaultDB();

	//������
	void ReadAll();
	void WriteAll();
};


//cpp

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::ReadAll()
{
	if (!FileOpenIn())
	{
		return;
	}

	cl_ourArray.clear();

	strPos it = 0;
	size_t n = BStringIO::ReadBInfo<size_t>(ReadStringFromFile(), it);

	for (size_t i = 0; i < n; ++i)
	{
		cl_ourArray.push_back(oneElementOfDB(ReadStringFromFile()));
	}

	cl_isChanged = false;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::WriteAll()
{
	AJIOB_ProgramLog("���������� ��������� � ����� " + cl_fileName);

	FileReset();

	//����� ���������� ����� � �����
	WriteStringToFile(BStringIO::GetBString(cl_ourArray.size()));
	
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		WriteStringToFile(it->BRead());
	}

	cl_isChanged = false;
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::DefaultDB(const std::string& wayToFile):AJIOB_BinaryFileInputOutput(wayToFile)
{
	
	ReadAll();
	//cl_isChanged = true;
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::~DefaultDB()
{
	if (cl_isChanged)
	{
		while (true)
		{
			std::cout << "�� ������ ��������� ���������? (Y - ��, N - ���). ������� ��� �����: ";
			auto ch = std::cin.get();
			ClearStream();

			if (ch == 'Y')
			{
				WriteAll();
				break;
			}

			if (ch == 'N')
			{
				break;
			}

			std::cout << "��������, ����� ����� �� ��������������. ����������, ��������� ����." << std::endl;
		}

	}
}
