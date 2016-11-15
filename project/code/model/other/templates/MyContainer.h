#pragma once
#include <iostream>
#include <vector>

#include "../../../view/headers/view.h"
#include "../../exceptions/AllExceptions.h"
#include "../../other/headers/StringFuncs.h"
//#include "../../binary input&output/templates/BStringIO.h"

#ifndef AJIOB_STRPOS
#define AJIOB_STRPOS
typedef unsigned int strPos;
#endif

template <typename Type>
class MyContainer : public std::vector<Type>
{
public:
	//std::string cl_whatWeStoreHere;

	std::string BRead() const;
	void BWrite(const std::string& bInfo, strPos& it);

	template <typename T>
	friend std::ostream& operator<< (std::ostream& s, const MyContainer<T>& that);
	template <typename T>
	friend std::istream& operator>> (std::istream& s, MyContainer<T>& that);

	bool OperationsWithElements();

	bool Add(bool isUnique /*= false*/);
	void Show() const;
	bool Update();
	bool Delete();

	int Find(const Type& elementToFind) const;

	//MyContainer& operator= (const MyContainer& x);
};




//cpp

template <typename Type>
std::string MyContainer<Type>::BRead() const
{
	std::string buffer = BStringIO::GetBString(this->size());
	for (auto it = this->begin(); it != this->end(); ++it)
	{
		buffer += BStringIO::GetBString(*it);
	}

	return buffer;
}

template <typename Type>
void MyContainer<Type>::BWrite(const std::string& bInfo, strPos& it)
{
	size_t numOfElements = BStringIO::ReadBInfo<size_t>(bInfo, it);
	this->clear();
	this->reserve(numOfElements);

	for (size_t i = 0; i < numOfElements; ++i)
	{
		this->push_back(BStringIO::ReadBInfo<Type>(bInfo, it));
	}
}

template <typename Type>
bool MyContainer<Type>::OperationsWithElements()
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить элемент" << std::endl;
		std::cout << "2) Просмотреть все элементы" << std::endl;
		std::cout << "3) Обновить информацию об элементе" << std::endl;
		std::cout << "4) Удалить элемент" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			if (this->Add(true)) isUpdated = true;
			break;
		case '2':
			this->Show();
			break;
		case '3':
			if (this->Update()) isUpdated = true;
			break;
		case '4':
			if (this->Delete())
			{
				isUpdated = true;
			}
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

template <typename Type>
bool MyContainer<Type>::Add(bool isUnique)
{
	ClearConsole();

	Type buff;

	do
	{
		OutputConsole("Введите информацию для добавления.");
		std::cin >> buff;
		ClearConsole();
		OutputConsole("Пожалуйста, проверьте правильность распознавания введенной Вами информации.");
		std::cout << buff;

		if (Stream::GetOnlyYN("Всё введено корректно?") == 'N')
		{
			continue;
		}

		if (isUnique && (Find(buff) >= 0))
		{
			if (Stream::GetOnlyYN("Извините, такой объект уже имеется. Отменить ввод?") == 'Y')
			{
				return false;
			}

			continue;
		}

		this->push_back(buff);
		return true;

	} while (true);
}

template <typename oneElementOfDB>
void MyContainer<oneElementOfDB>::Show() const
{
	try
	{
		if (this->empty())
		{
			OutputConsole("Пусто");
		}

		for (auto i = 0; i < this->size(); ++i)
		{
			OutputConsole(std::string("Элемент №") + AJIOBStringFuncs::IntToString(i + 1));
			std::cout << this->at(i) << std::endl;
		}
	}
	catch(MyException& e)
	{
		OutputConsole(std::string("У нас ошибка: ") + e.what());
	}
}

template <typename oneElementOfDB>
bool MyContainer<oneElementOfDB>::Update()
{
	int index = 0;
	do
	{
		try
		{
			index = Stream::InputInRange("Введите индекс элемента, который вы хотите обновить:", 1, static_cast<int> (this->size())) - 1;
			std::cout << this->at(index);
		}
		catch(const RangeException&)
		{
			OutputConsole("База данных пуста.");
			return false;
		}
	} while (Stream::GetOnlyYN("Вы хотите обновить именно этот элемент?") == 'N');

	return (this->at(index).UpdateMe());
}

template <typename oneElementOfDB>
bool MyContainer<oneElementOfDB>::Delete()
{
	ClearConsole();

	int delPos = 0;

	do
	{
		try
		{
			 delPos = Stream::InputInRange("Введите № удаляемого элемента:", 1, static_cast<int> (this->size())) - 1;
			 std::cout << this->at(delPos);

		}
		catch(const RangeException&)
		{
			OutputConsole("База данных пуста. Нечего удалять");
			return false;
		}
	} while (Stream::GetOnlyYN("Вы хотите удалить именно этот элемент?") == 'N');

	this->erase(this->begin() + delPos);
		

	return true;
}

template <typename Type>
int MyContainer<Type>::Find(const Type& elementToFind) const
{
	for (int i = 0; i < this->size(); i++)
	{
		if (this->at(i) == elementToFind)
		{
			return i;
		}
	}

	return -1;
}
/*
template <typename Type>
MyContainer<Type>& MyContainer<Type>::operator=(const MyContainer& x)
{
	std::vector<Type>::operator=(x);
	return (*this);
}*/

template <typename Type>
std::ostream& operator<<(std::ostream& s, const MyContainer<Type>& container)
{
	s << "Массив:" << std::endl;
	int i = 0;
	for (auto it = container.begin(); it != container.end(); ++i, ++it)
	{
		s << "\t[" << i << "]: " << *it << std::endl; 
	}
	return s;
}

template <typename Type>
std::istream& operator>>(std::istream& s, MyContainer<Type>& container)
{
	Type buff;
	s >> buff;
	container.push_back(buff);
	return s;
}