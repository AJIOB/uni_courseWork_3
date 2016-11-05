#include "../headers/AJIOBMenuClass.h"


DefaultID<AJIOBTypes::PrivelegeType> AJIOBMenuClass::Auth() const
{
	AuthClass localAuth(&cl_loginDB);
	DefaultID<AJIOBTypes::PrivelegeType> loggedID;

	do
	{
		try
		{
			loggedID = localAuth.run();

			if (loggedID.GetType() != AJIOBTypes::PrivelegeType::none)
			{
				break;
			}

			OutputConsole("Ошибка входа. У вас нет прав для доступа к каким-либо данным.");
		}
		catch(const NoLoginException&)
		{
			OutputConsole("Извините, вы ввели несуществующую комбинацию логина и пароля.");
		}
	}
	while (GetOnlyYN("Желаете повторить ввод?") == 'Y');

	return loggedID;
}

void AJIOBMenuClass::WithLoginDB()
{
	ClearConsole();
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
			cl_loginDB.Add();
			break;
		case '2':
			cl_loginDB.Show();
			break;
		case '3':
			cl_loginDB.Update();
			break;
		case '4':
			cl_loginDB.Delete();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::WithBooksDBs()
{
	//
	OutputConsole("Тут будет работа с книгами");
}

void AJIOBMenuClass::WithClientDB()
{
	//
	OutputConsole("Тут будет работа с базой читателей");
}

void AJIOBMenuClass::AdminMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как администратор библиотеки." << std::endl;

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
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::WorkerMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как работник библиотеки." << std::endl;
}

void AJIOBMenuClass::ClientMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как читатель библиотеки." << std::endl;
}

AJIOBMenuClass::AJIOBMenuClass() : cl_loginDB()
{

}

AJIOBMenuClass::~AJIOBMenuClass()
{
	//cl_loginDB.Unload();
}

int AJIOBMenuClass::run()
{
	int errorCode = 0;

	auto id = Auth();
	if (id.GetType() != AJIOBTypes::none)
	{
		errorCode = LoginSuccessfully(id);
	}

	return errorCode;
}

int AJIOBMenuClass::LoginSuccessfully(DefaultID<AJIOBTypes::PrivelegeType> loggedUserID)
{
	auto loggedType = loggedUserID.GetType();
	switch (loggedType)
	{
	case AJIOBTypes::user:
		ClientMenu();
		break;
	case AJIOBTypes::worker:
		WorkerMenu();
		break;
	case AJIOBTypes::admin:
		AdminMenu();
		break;
	default:
		OutputConsole("Извините, у вас нету доступа к каким-либо базам данных");
	}

	return 0;
}
