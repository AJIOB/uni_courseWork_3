#pragma once

#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>

#include "../../binary input&output/headers/BFileIO.h"
#include "../../binary input&output/templates/BStringIO.h"
//#include "../../../view/headers/view.h"
#include "../../other/headers/StringFuncs.h"
#include "../../../model/exceptions/AllExceptions.h"
#include "../../other/headers/CancelStruct.h"
#include "../../other/templates/MyContainer.h"

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

	std::stack<CancelStruct> cl_cancelStack;

	void WriteAllIfNeed();
	virtual bool SaveChangesToFile();

	void* GetMe();
	const void* GetMe() const;

	int Find(const oneElementOfDB& that);

	virtual bool GetAll(const bString& bStrQuery, bString& result) const;
	virtual bool GetOne(const bString& bStrQuery, bString& result) const;
	virtual bool GetAddress(const bString& bStrQuery, bString& result) const;
	virtual bool GetSize(const bString& bStrQuery, bString& result) const;

	virtual bool CancelLast(const bString& bStrQuery, bString& result);

	virtual bool ShowAll(const bString& bStrQuery, bString& result) const;
	virtual bool ShowOne(const bString& bStrQuery, bString& result) const;

	virtual void ReadAll();
	virtual void WriteAll();

	virtual bool Add(const bString& bStr/*, ilu& pos*/);
	virtual bool Get(const bString& bStrQuery, bString& result) const;
	virtual bool Update(const bString& bStr);
	virtual bool Delete(const bString& bStr);
	virtual bool Find(const bString& bStr, bString& result);
	virtual bool Show(const bString& bStrQuery, bString& result);
	virtual bool Cancel(const bString& bStrQuery, bString& result);

public:
	DefaultDB(const std::string& wayToFile, bool isReadOnly = false);
	virtual ~DefaultDB();
	
	bool Save();
	void Unload();
	
	oneElementOfDB& GetElement(int index);
	const oneElementOfDB& GetElement(int index) const;
	oneElementOfDB& operator[](int index);

	void SetReadOnly(const bool isReadOnly);
	bool GetReadOnly() const;

	virtual void SomethingIsChanged();

	virtual bool ExecuteQuery(const bString& query, bString& result);
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
	WriteStringToFile(BStringIO::MakeBString(cl_ourArray.size()));
	
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		WriteStringToFile(it->BRead());
	}

	FileClose();
	cl_isChanged = false;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Add(const bString& bStr)
{
	if (cl_readOnly)
	{
		return false;
	}

	strPos it = 0;

	oneElementOfDB buff(GetMe());

	//попытка распознавания бинарной строки
	try
	{
		buff = oneElementOfDB(bStr, it, GetMe());
	}
	catch (const OutOfBStringLimitException& e)
	{
		OutputConsole(e.what());
		return false;
	}

	if (Find(buff) >= 0)
	{
		return false;
	}

	if (it < bStr.size())
	{
		try
		{
			uli pos = BStringIO::ReadBInfo<uli>(bStr, it);
			//todo: test
			cl_ourArray.insert(cl_ourArray.begin() + pos, buff);
		}
		catch (const OutOfBStringLimitException& e)
		{
			OutputConsole(e.what());
			return false;
		}
	}
	//проверка запроса на законченность
	/*else if (it < cl_ourArray.size())
	{
		return false;
	}*/
	else
	{
		cl_ourArray.push_back(buff);
	}

	std::sort(cl_ourArray.begin(), cl_ourArray.end());

	//создание инверсного запроса
	CancelStruct tmp;
	time(&(tmp.time));
	tmp.query = "delete." + BStringIO::MakeBString(cl_ourArray.size() - 1);
	cl_cancelStack.push(tmp);

	cl_isChanged = true;

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Get(const bString& bStrQuery, bString& result) const
{
	result = "";

	std::string checkWord;
	bString bStrPart2;

	//todo: test
	AJIOBStringFuncs::BreakStringTo2Strings(bStrQuery, checkWord, bStrPart2, '.');

	if (checkWord == "all")
	{
		return GetAll(bStrPart2, result);
	}

	if (checkWord == "one")
	{
		return GetOne(bStrPart2, result);
	}

	if (checkWord == "address")
	{
		return GetAddress(bStrPart2, result);
	}

	if (checkWord == "size")
	{
		return GetSize(bStrPart2, result);
	}

	return false;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Update(const bString& bStr)
{
	if (cl_readOnly)
	{
		return false;
	}

	strPos it = 0;
	uli indexToUpdate = 0;
	oneElementOfDB newElem(GetMe());

	try
	{
		newElem = oneElementOfDB(bStr, it, GetMe());
		indexToUpdate = BStringIO::ReadBInfo<uli>(bStr, it);
	}
	catch(const OutOfBStringLimitException& e)
	{
		OutputConsole(e.what());
		return false;
	}

	if (indexToUpdate >= cl_ourArray.size())
	{
		return false;
	}

	//todo: test
	//создание инверсного запроса
	CancelStruct tmp;
	time(&(tmp.time));
	tmp.query = "update." + cl_ourArray[indexToUpdate].BRead() + BStringIO::MakeBString(indexToUpdate);
	cl_cancelStack.push(tmp);

	cl_ourArray[indexToUpdate] = newElem;

	cl_isChanged = true;

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Delete(const bString& bStr)
{
	if (cl_readOnly)
	{
		return false;
	}

	strPos it = 0;
	uli indexToDelete = 0;

	try
	{
		indexToDelete = BStringIO::ReadBInfo<uli>(bStr, it);
	}
	catch(const OutOfBStringLimitException& e)
	{
		OutputConsole(e.what());
		return false;
	}

	if (indexToDelete >= cl_ourArray.size())
	{
		return false;
	}

	//todo: test
	//создание инверсного запроса
	CancelStruct tmp;
	time(&(tmp.time));
	tmp.query = "add." + cl_ourArray[indexToDelete].BRead() + BStringIO::MakeBString(indexToDelete);
	cl_cancelStack.push(tmp);

	cl_ourArray.erase(cl_ourArray.begin() + indexToDelete);

	cl_isChanged = true;

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Find(const bString& bStr, bString& result)
{
	result = "";

	strPos it = 0;
	oneElementOfDB elemToFind;

	if (!BStringIO::ReadBStringFromDB(bStr, elemToFind))
	{
		return false;
	}

	result = BStringIO::MakeBString(Find(elemToFind));

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Show(const bString& bStr, bString& result)
{
	result = "";

	std::string checkWord;
	bString bStrTemp;

	AJIOBStringFuncs::BreakStringTo2Strings(bStr, checkWord, bStrTemp, '.');

	if (checkWord == "all")
	{
		return ShowAll(bStrTemp, result);
	}

	if (checkWord == "one")
	{
		return ShowOne(bStrTemp, result);
	}

	return false;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Cancel(const bString& bStrQuery, bString& result)
{
	if (cl_readOnly)
	{
		return false;
	}

	result = "";

	std::string checkWord;
	bString bStrPart2;

	//todo: test
	AJIOBStringFuncs::BreakStringTo2Strings(bStrQuery, checkWord, bStrPart2, '.');

	if (checkWord == "last")
	{
		return CancelLast(bStrPart2, result);
	}

	return false;
}

template <typename oneElementOfDB>
oneElementOfDB& DefaultDB<oneElementOfDB>::GetElement(int index)
{
	return cl_ourArray[index];
}

template <typename oneElementOfDB>
const oneElementOfDB& DefaultDB<oneElementOfDB>::GetElement(int index) const
{
	return cl_ourArray[index];
}

template <typename oneElementOfDB>
oneElementOfDB& DefaultDB<oneElementOfDB>::operator[](int index)
{
	return cl_ourArray[index];
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
void DefaultDB<oneElementOfDB>::SomethingIsChanged()
{
	cl_isChanged = true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::ExecuteQuery(const std::string& query, std::string& result)
{
	result = "";
	//todo: обработка других команд

	//select command to execute query
	std::string whatCommand;
	std::string rightPart;

	AJIOBStringFuncs::BreakStringTo2Strings(query, whatCommand, rightPart, '.');

	if (whatCommand == "add")
	{
		return Add(rightPart);
	}
	
	if (whatCommand == "get")
	{
		return Get(rightPart, result);
	}

	if (whatCommand == "update")
	{
		return Update(rightPart);
	}

	if (whatCommand == "delete")
	{
		return Delete(rightPart);
	}

	if (whatCommand == "find")
	{
		return Find(rightPart, result);
	}

	if (whatCommand == "show")
	{
		return Show(rightPart, result);
	}

	if (whatCommand == "cancel")
	{
		return Cancel(rightPart, result);
	}

	if (whatCommand == "save" && rightPart == "")
	{
		return Save();
	}

	return false;
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
const void* DefaultDB<oneElementOfDB>::GetMe() const
{
	return reinterpret_cast<const void*> (this);
}

template <typename oneElementOfDB>
int DefaultDB<oneElementOfDB>::Find(const oneElementOfDB& that)
{
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		if ((*it) == that)
		{
			return (it - cl_ourArray.begin());
		}
	}

	return -1;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::GetAll(const bString& bStrQuery, bString& result) const
{
	if (bStrQuery != "")
	{
		result = "";
		return false;
	}
	//todo: test
	result = ConvertVectorToMyContainer(cl_ourArray).BRead();

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::GetOne(const bString& bStrQuery, bString& result) const
{
	strPos it = 0;
	uli indexToRead = 0;

	try
	{
		indexToRead = BStringIO::ReadBInfo<uli>(bStrQuery, it);
	}
	catch(const OutOfBStringLimitException& e)
	{
		OutputConsole(e.what());
		return false;
	}

	if ((indexToRead >= cl_ourArray.size()) || (it < bStrQuery.size()))
	{
		return false;
	}

	result = cl_ourArray[indexToRead].BRead();

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::GetAddress(const bString& bStrQuery, bString& result) const 
{
	if (bStrQuery != "")
	{
		result = "";
		return false;
	}
	//todo: test
	
	result = BStringIO::MakeBString(GetMe());

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::GetSize(const bString& bStrQuery, bString& result) const
{
	if (bStrQuery != "")
	{
		result = "";
		return false;
	}
	//todo: test
	
	result = BStringIO::MakeBString(cl_ourArray.size());

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::CancelLast(const bString& bStrQuery, bString& result)
{
	result = "";

	if (bStrQuery != "" || cl_cancelStack.empty())
	{
		return false;
	}

	time_t currTime = 0;
	time(&currTime);

	CancelStruct cancel = cl_cancelStack.top();

	if ((cancel.time + liveTime) < currTime)
	{
		return false;
	}

	ExecuteQuery(cancel.query, result);

	//убираем запрос, который был составлен на отмену и тот, что отменили
	cl_cancelStack.pop();
	cl_cancelStack.pop();

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::ShowAll(const bString& bStrQuery, bString& result) const
{
	if (bStrQuery != "")
	{
		return false;
	}

	//получаем текстовую строку
	std::stringstream ssbuff;
	ssbuff << ConvertVectorToMyContainer(cl_ourArray);

	result = BStringIO::MakeBString(ssbuff.str());

	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::ShowOne(const bString& bStrQuery, bString& result) const
{
	
	uli indexToRead = 0;
	if (!BStringIO::ReadBStringFromDB(bStrQuery, indexToRead))
	{
		return false;
	}

	if (indexToRead >= cl_ourArray.size())
	{
		return false;
	}

	//получаем текстовую строку
	std::stringstream ssbuff;
	ssbuff << cl_ourArray[indexToRead];

	result = BStringIO::MakeBString(ssbuff.str());

	return true;
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
bool DefaultDB<oneElementOfDB>::SaveChangesToFile()
{
	if (cl_readOnly || !cl_isChanged)
	{
		return false;
	}

	WriteAll();
	
	return true;
}

template <typename oneElementOfDB>
bool DefaultDB<oneElementOfDB>::Save()
{
	return SaveChangesToFile();
}

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::Unload()
{
	WriteAllIfNeed();
}


/*
template <typename oneElementOfDB>
int DefaultDB<oneElementOfDB>::Add(bool isUnique)
{
	if (cl_readOnly)
	{
		return -1;
	}

	ClearConsole();

	oneElementOfDB buff(GetMe());

	do
	{
		std::cin >> buff;
		ClearConsole();
		OutputConsole("Пожалуйста, проверьте правильность распознавания введенной Вами информации");
		std::cout << buff;

		if (Stream::GetOnlyYN("Всё введено корректно?") == 'N')
		{
			continue;
		}

		auto findIndex = Find(buff);

		if (isUnique && (findIndex >= 0))
		{
			if (Stream::GetOnlyYN("Извините, такой объект уже имеется. Отменить ввод?") == 'Y')
			{
				return findIndex;
			}

			continue;
		}

		cl_ourArray.push_back(buff);
		cl_isChanged = true;

		return (cl_ourArray.size() - 1);
	} while (true);
}*/
/*
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
		catch(const RangeException&)
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
		catch(const RangeException&)
		{
			OutputConsole("База данных пуста. Нечего удалять");
			return;
		}

	} while (Stream::GetOnlyYN("Вы хотите удалить именно этот элемент?") == 'N');

	cl_ourArray.erase(cl_ourArray.begin() + delPos);

	cl_isChanged = true;
}
*/