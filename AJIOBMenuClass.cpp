#include "AJIOBMenuClass.h"

void AJIOBMenuClass::WithLoginDB()
{
	system("cls");
	std::cout << "Взаимодействие с базой данных логинов и паролей" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить пользователя" << std::endl;
		std::cout << "2) Просмотреть всех пользователей" << std::endl;
		std::cout << "3) Обновить информацию о пользователе" << std::endl;
		std::cout << "4) Удалить пользователя" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Get();

		switch (k)
		{
		case '0':
			return;
		case '1':
			//WithLoginDB();
			break;
		case '2':
			//WithBooksDBs();
			break;
		case '3':
			//WithClientDB();
			break;
		default:
			std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
		}

		system("pause");
		system("cls");
	}
	while (true);
}

void AJIOBMenuClass::WithBooksDBs()
{
	//
	std::cout << "Тут будет работа с книгами" << std::endl;
}

void AJIOBMenuClass::WithClientDB()
{
	//
	std::cout << "Тут будет работа с базой читателей" << std::endl;
}

void AJIOBMenuClass::AdminMenu()
{
	system("cls");
	std::cout << "Вы зашли под правами Администратора" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, с какой базой данных вы хотите поработать:" << std::endl;
		std::cout << "1) Логины и пароли пользователей" << std::endl;
		std::cout << "2) Книги" << std::endl;
		std::cout << "3) Управление читателями" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Get();

		switch (k)
		{
		case '0':
			return;
		case '1':
			WithLoginDB();
			break;
		case '2':
			WithBooksDBs();
			break;
		case '3':
			WithClientDB();
			break;
		default:
			std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
		}

		system("pause");
		system("cls");
	}
	while (true);
}

void AJIOBMenuClass::WorkerMenu()
{
}

void AJIOBMenuClass::ClientMenu()
{
}

int AJIOBMenuClass::run(DefaultID<AJIOBTypes::PrivelegeType> loggedUser)
{
	//
	return 0;
}
