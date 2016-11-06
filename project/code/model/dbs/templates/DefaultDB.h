#pragma once

#include <vector>

#include "../../binary input&output/headers/BFileIO.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../../view/headers/view.h"
#include "../../other/headers/StringFuncs.h"
#include "../../../model/exceptions/AllExceptions.h"

template <typename oneElementOfDB>
class DefaultDB : public AJIOB_BinaryFileInputOutput
{
protected:
	//����
	std::vector<oneElementOfDB> cl_ourArray;

	//���� ���������
	bool cl_isChanged;

	//��� ������ ��� ���?
	bool cl_readOnly;

//protected:
	void WriteAllIfNeed();

	virtual void UpdateElementWithIndex(int index) = 0;

public:
	DefaultDB(const std::string& wayToFile, bool isReadOnly = true);
	~DefaultDB();

	//������
	virtual void ReadAll();
	virtual void WriteAll();

	virtual void Add();
	virtual void Show() const;
	virtual void Update();
	virtual void Delete();
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
		it = 0;
		cl_ourArray.push_back(oneElementOfDB(ReadStringFromFile(), it));
	}

	cl_isChanged = false;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::WriteAll()
{
	if (cl_readOnly)
	{
		return;
	}

	OutputLog("���������� ��������� � ����� " + cl_fileName);

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
void DefaultDB<oneElementOfDB>::Add()
{
	if (cl_readOnly)
	{
		return;
	}

	ClearConsole();

	oneElementOfDB buff;

	do
	{
		std::cin >> buff;
		ClearConsole();
		OutputConsole("����������, ��������� ������������ ������������� ��������� ���� ����������");
		std::cout << buff;
	} while (GetOnlyYN("��������� ���� ������ ����������?") == 'Y');

	cl_ourArray.push_back(buff);
	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Show() const
{
	try
	{
		for (auto i = 0; i < cl_ourArray.size(); ++i)
		{
			OutputConsole(StringCat(std::string("������� �"), i + 1));
			std::cout << cl_ourArray[i] << std::endl;
		}
	}
	catch(MyException& e)
	{
		OutputConsole(std::string("� ��� ������: ") + e.what());
	}
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Update()
{
	int index = 0;
	do
	{
		try
		{
			index = InputInRange("������� ������ ��������, ������� �� ������ ��������:", 1, static_cast<int> (cl_ourArray.size())) - 1;
			std::cout << cl_ourArray[index];
		}
		catch(const MinMaxException&)
		{
			OutputConsole("���� ������ �����.");
			return;
		}
	} while (GetOnlyYN("�� ������ �������� ������ ���� �������?") == 'N');

	UpdateElementWithIndex(index);

	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Delete()
{
	if (cl_readOnly)
	{
		return;
	}

	ClearConsole();

	try
	{
		int delPos = InputInRange("������� � ���������� ��������:", 1, static_cast<int> (cl_ourArray.size())) - 1;
		cl_ourArray.erase(cl_ourArray.begin() + delPos);
	}
	catch(const MinMaxException&)
	{
		OutputConsole("���� ������ �����. ������ �������");
		return;
	}

	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::WriteAllIfNeed()
{
	if (cl_readOnly || !cl_isChanged)
	{
		return;
	}

	if (GetOnlyYN("�� ������ ��������� ���������?") == 'Y')
	{
		WriteAll();
	}
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::DefaultDB(const std::string& wayToFile, bool isReadOnly = true) : AJIOB_BinaryFileInputOutput(wayToFile)
{
	//ReadAll();

	cl_readOnly = isReadOnly;
	cl_isChanged = false;
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::~DefaultDB()
{
	WriteAllIfNeed();
}
