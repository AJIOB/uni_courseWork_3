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
	//поля
	std::vector<oneElementOfDB> cl_ourArray;

	//флаг изменения
	bool cl_isChanged;

	//для чтения или нет?
	bool cl_readOnly;

//protected:
	void WriteAllIfNeed();

	virtual bool UpdateElement(oneElementOfDB&) = 0;
	void* GetMe();

public:
	DefaultDB(const std::string& wayToFile, bool isReadOnly = true);
	virtual ~DefaultDB();

	virtual void SaveChangesToFile();

	//методы
	virtual void ReadAll();
	virtual void WriteAll();

	virtual void Add();
	virtual void Show() const;
	virtual void Update();
	virtual void Delete();

	void SetReadOnly(const bool isReadOnly);
	bool GetReadOnly() const;
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
		cl_ourArray.push_back(oneElementOfDB(ReadStringFromFile(), it, GetMe()));
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
	if (cl_readOnly)
	{
		return;
	}

	ClearConsole();

	oneElementOfDB buff(GetMe());

	do
	{
		std::cin >> buff;
		ClearConsole();
		OutputConsole("Пожалуйста, проверьте правильность распознавания введенной Вами информации");
		std::cout << buff;
	} while (Stream::GetOnlyYN("Всё введено корректно?") == 'N');

	cl_ourArray.push_back(buff);
	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Show() const
{
	try
	{
		if (cl_ourArray.empty())
		{
			OutputConsole("Пусто");
		}

		for (auto i = 0; i < cl_ourArray.size(); ++i)
		{
			OutputConsole(std::string("Элемент №") + AJIOBStringFuncs::IntToString(i + 1));
			std::cout << cl_ourArray[i] << std::endl;
		}
	}
	catch(MyException& e)
	{
		OutputConsole(std::string("У нас ошибка: ") + e.what());
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
			index = Stream::InputInRange("Введите индекс элемента, который вы хотите обновить:", 1, static_cast<int> (cl_ourArray.size())) - 1;
			std::cout << cl_ourArray[index];
		}
		catch(const MinMaxException&)
		{
			OutputConsole("База данных пуста.");
			return;
		}
	} while (Stream::GetOnlyYN("Вы хотите обновить именно этот элемент?") == 'N');

	if (UpdateElement(cl_ourArray[index]))
	{
		cl_isChanged = true;
	}
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Delete()
{
	if (cl_readOnly)
	{
		return;
	}

	ClearConsole();

	int delPos = 0;

	do
	{
		try
		{
			 delPos = Stream::InputInRange("Введите № удаляемого элемента:", 1, static_cast<int> (cl_ourArray.size())) - 1;
			 std::cout << cl_ourArray.at(delPos);
		}
		catch(const MinMaxException&)
		{
			OutputConsole("База данных пуста. Нечего удалять");
			return;
		}

	} while (Stream::GetOnlyYN("Вы хотите обновить именно этот элемент?") == 'N');

	cl_ourArray.erase(cl_ourArray.begin() + delPos);

	cl_isChanged = true;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::SetReadOnly(const bool isReadOnly)
{
	if (cl_readOnly)
	{
		ReadAll();
	}
	else
	{
		WriteAllIfNeed();
	}

	cl_readOnly = isReadOnly;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::GetReadOnly() const
{
	return cl_readOnly;
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::WriteAllIfNeed()
{
	if (cl_readOnly || !cl_isChanged)
	{
		return;
	}

	if (Stream::GetOnlyYN("Вы хотите сохранить изменения?") == 'Y')
	{
		WriteAll();
	}

	//нужно было сохранять
	cl_isChanged = false;
}

template <typename oneElementOfDB>
void* DefaultDB<oneElementOfDB>::GetMe()
{
	return reinterpret_cast<void*> (this);
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

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::SaveChangesToFile()
{
	if (cl_readOnly || !cl_isChanged)
	{
		OutputConsole("В файле записана актуальная информация");
		return;
	}

	WriteAll();
	OutputConsole("Все изменения успешно сохранены");
}
