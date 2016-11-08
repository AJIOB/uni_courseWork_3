#include "../headers/AJIOBMenuClass.h"


OneElementOf::Auth AJIOBMenuClass::Auth()
{
	AuthClass localAuth(&cl_loginDB);
	OneElementOf::Auth loggedAuthElement(&cl_loginDB);

	do
	{
		try
		{
			loggedAuthElement = localAuth.run();

			if (loggedAuthElement.GetLogin().GetType() != AJIOBTypes::PrivelegeType::none)
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
	while (Stream::GetOnlyYN("Желаете повторить ввод?") == 'Y');

	return loggedAuthElement;
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
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			cl_loginDB.Save();
			break;
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

void AJIOBMenuClass::WithPublisherDB()
{/*
	ClearConsole();
	std::cout << "Взаимодействие с базой данных издательств" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить издательство" << std::endl;
		std::cout << "2) Просмотреть все издательства" << std::endl;
		std::cout << "3) Обновить информацию об издательстве" << std::endl;
		std::cout << "4) Удалить издательство" << std::endl;
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			cl_publishersDB.Save();
			break;
		case '0':
			return;
		case '1':
			cl_publishersDB.Add();
			break;
		case '2':
			cl_publishersDB.Show();
			break;
		case '3':
			cl_publishersDB.Update();
			break;
		case '4':
			cl_publishersDB.Delete();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);*/
}

void AJIOBMenuClass::WithCountryDB()
{
	ClearConsole();
	std::cout << "Взаимодействие с базой данных ISBN номеров регионов" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить комбинацию ISBN номер региона" << std::endl;
		std::cout << "2) Просмотреть все комбинации ISBN номеров" << std::endl;
		std::cout << "3) Обновить информацию о комбинации ISBN номеров" << std::endl;
		std::cout << "4) Удалить комбинацию" << std::endl;
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			cl_countriesDB.Save();
			break;
		case '0':
			return;
		case '1':
			cl_countriesDB.Add();
			break;
		case '2':
			cl_countriesDB.Show();
			break;
		case '3':
			cl_countriesDB.Update();
			break;
		case '4':
			cl_countriesDB.Delete();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::AdminMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как администратор библиотеки." << std::endl;

	do
	{
		std::cout << "Выберите, пожалуйста, с какой базой данных вы хотите поработать:" << std::endl;
		std::cout << "1) Логины и пароли пользователей" << std::endl;
		std::cout << "2) Управление ISBN стран" << std::endl;
		std::cout << "3) Управление издательствами" << std::endl;
		std::cout << "8) Управление своим профилем" << std::endl;
		std::cout << "9) Сохранить все изменения" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		/*try
		{*/
		switch (k)
		{
		case '0':
			return;
		case '1':
			WithLoginDB();
			break;
		case '2':
			WithCountryDB();
			break;
		case '3':
			WithPublisherDB();
			break;
		case '8':
			ManageYourProfile();
			break;
		case '9':
			SaveAllChanges();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}
		/*}
		catch(KeyException&)
		{
			OutputConsole("Key");
		}*/

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::WorkerMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как работник библиотеки." << std::endl;
	/*
	do
	{
		std::cout << "Выберите, пожалуйста, с какой базой данных вы хотите поработать:" << std::endl;
		std::cout << "2) Книги" << std::endl;
		std::cout << "3) Управление читателями" << std::endl;
		std::cout << "8) Управление своим профилем" << std::endl;
		std::cout << "9) Сохранить все изменения" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '0':
			return;
		case '1':
			WithLoginDB();
			break;
		case '2':
			WithPublisherDB();
			break;
		case '3':
			WithClientDB();
			break;
		case '8':
			ManageYourProfile();
			break;
		case '9':
			SaveAllChanges();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);*/
}

void AJIOBMenuClass::ClientMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как читатель библиотеки." << std::endl;
}

void AJIOBMenuClass::SaveAllChanges()
{
	cl_loginDB.Save();
	//cl_publishersDB.Save();
	cl_countriesDB.Save();
}

void AJIOBMenuClass::ManageYourProfile()
{
	ClearConsole();

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Изменение пароля" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '0':
			cl_loginDB.Save();
			return;
		case '1':
			ChangeYourPassword();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::ChangeYourPassword()
{
	ClearConsole();

	auto index = cl_loginDB.Find(cl_loggedUser);
	if (index < 0)
	{
		throw MyException("Видимо, что-то пошло не так");
	}

	if (cl_loginDB[index].InputNewPassword())
	{
		cl_loginDB.SomethingIsChanged();
	}

	cl_loggedUser = cl_loginDB[index];
	cl_loginDB.Save();
}

AJIOBMenuClass::AJIOBMenuClass() : cl_loginDB(), /*cl_publishersDB(), */cl_loggedUser(&cl_loginDB)
{

}

AJIOBMenuClass::~AJIOBMenuClass()
{
	//cl_loginDB.Unload();
}

int AJIOBMenuClass::run()
{
	int errorCode = 0;

	auto user = Auth();
	if (user.GetLogin().GetType() != AJIOBTypes::none)
	{
		this->cl_loggedUser = user;
		errorCode = LoginSuccessfully();
	}

	return errorCode;
}

int AJIOBMenuClass::LoginSuccessfully()
{
	auto loggedType = cl_loggedUser.GetLogin().GetType();
	switch (loggedType)
	{
	case AJIOBTypes::PrivelegeType::user:
		ClientMenu();
		break;
	case AJIOBTypes::PrivelegeType::worker:
		WorkerMenu();
		break;
	case AJIOBTypes::PrivelegeType::admin:
		AdminMenu();
		break;
	default:
		OutputConsole("Извините, у вас нету доступа к каким-либо базам данных");
	}

	return 0;
}
