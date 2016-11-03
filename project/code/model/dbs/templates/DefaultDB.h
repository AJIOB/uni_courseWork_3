#pragma once

#include <vector>

#include "../../binary input&output/headers/BFileIO.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../../view/headers/view.h"

#include "../../other/headers/StringFuncs.h"

template <typename oneElementOfDB>
class DefaultDB : public AJIOB_BinaryFileInputOutput
{
protected:
	//поля
	std::vector<oneElementOfDB> cl_ourArray;

	//флаг изменения
	bool cl_isChanged;

	//для чтения или нет?
	bool cl_readOnly;

protected:
	void WriteAllIfNeed();

public:
	DefaultDB(const std::string& wayToFile, bool isReadOnly = true);
	~DefaultDB();

	//методы
	void ReadAll();
	void WriteAll();

	void Add();
	void Show() const;
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
	OutputLog("Сохранение изменений в файле " + cl_fileName);

	FileReset();

	//Пишем количество строк в файле
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
	oneElementOfDB buff;

	do
	{
		std::cin >> buff;
		system("cls");
		OutputInfo("Пожалуйста, проверьте правильность распознавания введенной Вами информации");
		std::cout << buff;
		OutputInfo("Повторить ввод данной информации (Y - да, N - нет)? <нет>");
	} while (Get() == 'Y');

	cl_ourArray.push_back(buff);
	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Show() const
{
	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		OutputInfo(StringCat(std::string("Элемент №"), i));
		std::cout << cl_ourArray[i] << std::endl;
	}
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::WriteAllIfNeed()
{
	if (!cl_readOnly && cl_isChanged)
	{
		while (true)
		{
			OutputInfo("Вы хотите сохранить изменения? (Y - да, N - нет). Введите ваш ответ: ");
			auto ch = Get();

			if (ch == 'Y')
			{
				WriteAll();
				break;
			}

			if (ch == 'N')
			{
				break;
			}

			OutputWarning("Извините, такой ответ не поддерживается. Пожалуйста, повторите ввод.");
		}

	}
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::DefaultDB(const std::string& wayToFile, bool isReadOnly = true) : AJIOB_BinaryFileInputOutput(wayToFile)
{
	ReadAll();

	cl_readOnly = isReadOnly;

	//cl_isChanged = true;
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::~DefaultDB()
{
	WriteAllIfNeed();
}
