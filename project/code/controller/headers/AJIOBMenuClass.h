#pragma once

#include "../headers/authClass.h"
#include "AJIOB_DBSystem.h"

class AJIOBMenuClass
{
	AJIOB_DBSystem cl_localCopyOfDBSys;

	AJIOBTypes::PrivelegeType::PrivelegeType cl_authPriveleges;
	
	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();

	template <typename Type>
	bool LocalGetFromDB(const std::string& req, Type& elem);
	bool LocalGetFromDB(const std::string& req);

	template <typename oneElemOfDB>
	void SelectFunction(const std::string& dbName);

	template <typename oneElemOfDB>
	void Add(const std::string& dbName);
	template <typename oneElemOfDB>
	void Show(const std::string& dbName);
	template <typename oneElemOfDB>
	void Update(const std::string& dbName);
	template <typename oneElemOfDB>
	void Delete(const std::string& dbName);
	template <typename oneElemOfDB>
	void Cancel(const std::string& dbName);
	template <typename oneElemOfDB>
	void Save(const std::string& dbName);

	void SaveAll();

public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run();
};





//cpp part 1

template <typename Type>
bool AJIOBMenuClass::LocalGetFromDB(const bString& req, Type& elem)
{
	bString res;

	if (!cl_localCopyOfDBSys.ExecuteQuery(req, res))
	{
		OutputConsole("При получении ответа БД произошла какая-то ошибка");
		return false;
	}

	Type buff(elem);

	if (!BStringIO::ReadBStringFromDB(res, buff))
	{
		OutputConsole("Ошибка. Выходим...");
		return false;
	}

	elem = buff;
	return true;
}

template <typename oneElemOfDB>
void AJIOBMenuClass::SelectFunction(const std::string& dbName)
{
	ClearConsole();

	do
	{
		std::cout << "Взаимодействие с базой данных " << dbName << std::endl;
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить элементы" << std::endl;
		std::cout << "2) Просмотреть все элементы" << std::endl;
		std::cout << "3) Обновить информацию об элементе" << std::endl;
		std::cout << "4) Удалить элемент" << std::endl;
		std::cout << "5) Отмена последнего действия" << std::endl;
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			Save<oneElemOfDB>(dbName);
			break;
		case '0':
			return;
		case '1':
			Add<oneElemOfDB>(dbName);
			break;
		case '2':
			Show<oneElemOfDB>(dbName);
			break;
		case '3':
			Update<oneElemOfDB>(dbName);
			break;
		case '4':
			Delete<oneElemOfDB>(dbName);
			break;
		case '5':
			Cancel<oneElemOfDB>(dbName);
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Add(const std::string& dbName)
{
	ClearConsole();

	void* parent = nullptr;

	//получим адрес родительской базы
	if (!LocalGetFromDB(dbName + ".get.address", parent))
	{
		return;
	}

	oneElemOfDB buff(parent);

	do
	{
		try
		{
			std::cin >> buff;
		}
		catch (const RepeatException&)
		{
			return;
		}

		ClearConsole();
		OutputConsole("Пожалуйста, проверьте правильность распознавания введенной Вами информации");
		std::cout << buff;

		if (Stream::GetOnlyYN("Всё введено корректно?") == 'N')
		{
			continue;
		}

		//поиск на совпадения
		int findIndex = -1;

		if (!LocalGetFromDB(dbName + ".find." + buff.BRead(), findIndex))
		{
			return;
		}

		//проверка индекса из поиска
		if (findIndex >= 0)
		{
			if (Stream::GetOnlyYN("Извините, такой объект уже имеется. Отменить ввод?") == 'Y')
			{
				return;
			}

			continue;
		}

		if (!LocalGetFromDB(dbName + ".add." + buff.BRead()))
		{
			OutputConsole("При добавлении произошла какая-то ошибка");
		}
		else
		{
			OutputConsole("Добавление прошло успешно");
		}

		return;
	} while (true);
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Show(const std::string& dbName)
{
	std::string result;
	if (!LocalGetFromDB(dbName + ".show.all", result))
	{
		return;
	}
	
	if (result.empty())
	{
		OutputConsole("Пусто");
		return;
	}

	OutputConsole(result);
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Update(const std::string& dbName)
{
	//todo: test&check
	ClearConsole();

	void* parent = nullptr;

	//получим адрес родительской базы
	if (!LocalGetFromDB(dbName + ".get.address", parent))
	{
		return;
	}

	oneElemOfDB elemToUpdate(parent);

	size_t size = 0;

	//получим размер массива
	if (!LocalGetFromDB(dbName + ".get.size", size))
	{
		return;
	}


	uli updatePos = 0;

	do
	{
		try
		{
			updatePos = Stream::InputInRange("Введите № элемента, который вы хотите обновить:", 1, static_cast<int> (size)) - 1;
		}
		catch(const RangeException&)
		{
			OutputConsole("База данных пуста. Нечего обновлять");
			return;
		}

		//получаем обновляемый элемент
		bString res;

		if (!cl_localCopyOfDBSys.ExecuteQuery(dbName + ".get.one." + BStringIO::MakeBString(updatePos), res))
		{
			OutputConsole("При получении ответа БД произошла какая-то ошибка");
			return;
		}

		try
		{
			strPos it = 0;
			elemToUpdate =  oneElemOfDB(res, it, parent);
		}
		catch(const OutOfBStringLimitException& e)
		{
			OutputError(e.what());
			return;
		}

		//показываем обновляемый элемент
		std::cout << elemToUpdate << std::endl;

	} while (Stream::GetOnlyYN("Вы хотите обновить именно этот элемент?") == 'N');

	elemToUpdate.UpdateMe();

	if (!LocalGetFromDB(dbName + ".update." + elemToUpdate.BRead() + BStringIO::MakeBString(updatePos)))
	{
		OutputConsole("При обновлении произошла какая-то ошибка");
	}
	else
	{
		OutputConsole("Обновление прошло успешно");
	}
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Delete(const std::string& dbName)
{
	ClearConsole();

	size_t size = 0;

	//получим размер массива
	if (!LocalGetFromDB(dbName + ".get.size", size))
	{
		return;
	}

	uli delPos = 0;

	do
	{
		try
		{
			delPos = Stream::InputInRange("Введите № удаляемого элемента:", 1, static_cast<int> (size)) - 1;
		}
		catch(const RangeException&)
		{
			OutputConsole("База данных пуста. Нечего удалять");
			return;
		}

		//показываем удаляемый элемент
		std::string resToShow;
		if (!LocalGetFromDB(dbName + ".show.one." + BStringIO::MakeBString(delPos), resToShow))
		{
			return;
		}

		std::cout << resToShow << std::endl;

	} while (Stream::GetOnlyYN("Вы хотите удалить именно этот элемент?") == 'N');

	if (!LocalGetFromDB(dbName + ".delete." + BStringIO::MakeBString(delPos)))
	{
		OutputConsole("При удалении произошла какая-то ошибка");
	}
	else
	{
		OutputConsole("Удаление прошло успешно");
	}
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Cancel(const std::string& dbName)
{
	if (!LocalGetFromDB(dbName + ".cancel.last"))
	{
		OutputConsole("Возможно, нечего отменять");
		return;
	}
	
	OutputConsole("Последнее действие отменено");
}

template <typename oneElemOfDB>
void AJIOBMenuClass::Save(const std::string& dbName)
{
	if (!LocalGetFromDB(dbName + ".save"))
	{
		OutputConsole("В файле записана актуальная информация");
		return;
	}
	
	OutputConsole("Все изменения успешно сохранены");
}

/*
	OneElementOf::Auth Auth();
	int LoginSuccessfully();

	void WithLoginDB();
	void WithCountryDB();
	void WithPublicationsDB();
	void WithCopiesDB();

	//

	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	
	void SaveAllChanges();

	void ManageYourProfile();
	void ChangeYourPassword();
	/*/
