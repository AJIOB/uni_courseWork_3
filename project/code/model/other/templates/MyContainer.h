#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../../../view/headers/view.h"
#include "../../exceptions/AllExceptions.h"
#include "../../other/headers/StringFuncs.h"
#include "../headers/typedefs.h"
#include "../../binary input&output/templates/BStringIO.h"


template <typename Type>
class MyContainer : public std::vector<Type>
{
public:
	//std::string cl_whatWeStoreHere;

	std::string BRead() const;
	void BWrite(const bString& bInfo, strPos& it);

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
	void PushWithSort(const Type& elem);
};

//спецификация шаблонов
template <typename Type>
MyContainer<Type> ConvertVectorToMyContainer(const std::vector<Type>& vec);






//cpp

template <typename Type>
bString MyContainer<Type>::BRead() const
{
	std::string buffer = BStringIO::MakeBString(this->size());
	for (auto it = this->begin(); it != this->end(); ++it)
	{
		buffer += BStringIO::MakeBString(*it);
	}

	return buffer;
}

template <typename Type>
void MyContainer<Type>::BWrite(const bString& bInfo, strPos& it)
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

		if (typeid(Type) == typeid(std::string))
		{
			std::cout << std::endl;
		}

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

		PushWithSort(buff);

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
{//todo
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


template <>
inline bool MyContainer<std::string>::Update()
{//todo
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

	//особенности для std::string
	if (!Add(true))
	{
		return false;
	}

	//заменяем нужный элемент
	this->at(index) = this->back();
	this->pop_back();

	//todo: sort
	std::sort(this->begin(), this->end());

	return true;
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

			if (typeid(oneElementOfDB) == typeid(std::string))
			{
				std::cout << std::endl;
			}
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

template <typename Type>
void MyContainer<Type>::PushWithSort(const Type& elem)
{
	this->push_back(elem);
	//todo: sort
	std::sort(this->begin(), this->end());
}

template <typename Type>
MyContainer<Type> ConvertVectorToMyContainer(const std::vector<Type>& vec)
{
	MyContainer<Type> toReturn;

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		toReturn.push_back(*it);
	}

	return toReturn;
}

template <typename Type>
std::ostream& operator<<(std::ostream& s, const MyContainer<Type>& container)
{
	try
	{
		if (container.empty())
		{
			s << "Пусто";
		}
		else
		{
			s << "Массив:" << std::endl;
		}

		for (auto i = 0; i < container.size(); ++i)
		{
			//OutputConsole(std::string("Элемент №") + AJIOBStringFuncs::IntToString(i + 1));
			s << /*"\t["*/ "[" << i << "]: " /*<< std::endl*/ << container[i] << std::endl; 
		}
	}
	catch(MyException& e)
	{
		OutputConsole(std::string("У нас ошибка: ") + e.what());
	}

	return s;
}

template <typename Type>
std::istream& operator>>(std::istream& s, MyContainer<Type>& container)
{
	Type buff;
	s >> buff;
	container.PushWithSort(buff);
	return s;
}