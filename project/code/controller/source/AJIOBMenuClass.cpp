#include "../headers/AJIOBMenuClass.h"

void AJIOBMenuClass::AdminMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как администратор библиотеки." << std::endl;

	do
	{
		std::cout << "Выберите, пожалуйста, с какой базой данных вы хотите поработать:" << std::endl;
		std::cout << "1) Управление пользователями" << std::endl;
		std::cout << "2) Управление ISBN регионов и их издательств" << std::endl;
		std::cout << "3) Управление изданиями" << std::endl;
		std::cout << "4) Управление экземплярами изданий" << std::endl;
		//std::cout << "5) BETA Управление пользователями" << std::endl;
		//std::cout << "8) Управление своим профилем" << std::endl;
		std::cout << "9) Сохранить все изменения" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		/*try
		{*/
		switch (k)
		{
		case '0':
			return;//TODO: check & test
		case '1':
			SelectFunction<OneElementOf::User>("users");
			break;
		case '2':
			SelectFunction<OneElementOf::Country>("countries");
			break;
		case '3':
			SelectFunction<OneElementOf::Publication>("publications");
			break;
		case '4':
			SelectFunction<OneElementOf::Copies>("bookcopies");
			break;/*
		case '5':
			SelectFunction<OneElementOf::User>("users");
			break;
			/*
		case '8':
			ManageYourProfile();
			break;*/
		case '9':
			SaveAll();
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
}

void AJIOBMenuClass::ClientMenu()
{
	ClearConsole();
	std::cout << "Здравствуйте. Вы зашли как читатель библиотеки." << std::endl;
}

bool AJIOBMenuClass::LocalGetFromDB(const std::string& req)
{
	bString res;

	if (!cl_localCopyOfDBSys.ExecuteQuery(req, res))
	{
		OutputConsole("При получении ответа БД произошла какая-то ошибка");
		return false;
	}

	return true;
}

void AJIOBMenuClass::SaveAll()
{
	bString result;

	if (cl_localCopyOfDBSys.ExecuteQuery("saveall", result))
	{
		OutputConsole("Все изменения успешно сохранены");
		return;
	}

	OutputConsole("В файле записана актуальная информация");
}

AJIOBMenuClass::AJIOBMenuClass() : cl_localCopyOfDBSys()
{
	cl_authPriveleges = cl_localCopyOfDBSys.RunLoginProcess();
}

AJIOBMenuClass::~AJIOBMenuClass()
{
}

int AJIOBMenuClass::run()
{
	if (cl_authPriveleges == AJIOBTypes::PrivelegeType::none)
	{
		OutputConsole("Извините, у вас нету доступа к каким-либо базам данных");
		return  1;
	}

	//auto loggedType = cl_authPriveleges.GetLogin().GetType();
	switch (cl_authPriveleges)
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
		return 1;
	}

	return 0;
}

/*
int AJIOBMenuClass::LoginSuccessfully()
{
	auto loggedType = cl_authPriveleges.GetLogin().GetType();
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
*/

/*
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
			cl_loginDB.Get();
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
			cl_countriesDB.Get();
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

void AJIOBMenuClass::WithPublicationsDB()
{
	ClearConsole();
	std::cout << "Взаимодействие с базой данных изданий" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить издание" << std::endl;
		std::cout << "2) Просмотреть все издания" << std::endl;
		std::cout << "3) Обновить информацию об издании" << std::endl;
		std::cout << "4) Удалить издание" << std::endl;
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			cl_publicationsDB.Save();
			break;
		case '0':
			return;
		case '1':
			cl_publicationsDB.Add();
			break;
		case '2':
			cl_publicationsDB.Get();
			break;
		case '3':
			cl_publicationsDB.Update();
			break;
		case '4':
			cl_publicationsDB.Delete();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void AJIOBMenuClass::WithCopiesDB()
{
	ClearConsole();
	std::cout << "Взаимодействие с базой данных копий книг в библиотеке" << std::endl;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Добавить экземпляры в библиотеку" << std::endl;
		std::cout << "2) Просмотреть все экземпляры" << std::endl;
		std::cout << "3) Обновить информацию об экземпляре" << std::endl;
		std::cout << "4) Удалить все экземпляры издания" << std::endl;
		std::cout << "9) Сохранить информацию в файл" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();

		switch (k)
		{
		case '9':
			cl_copiesDB.Save();
			break;
		case '0':
			return;
		case '1':
			cl_copiesDB.Add();
			break;
		case '2':
			cl_copiesDB.Get();
			break;
		case '3':
			cl_copiesDB.Update();
			break;
		case '4':
			cl_copiesDB.Delete();
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}*/

/*
void AJIOBMenuClass::SaveAllChanges()
{
	cl_loginDB.Save();
	cl_countriesDB.Save();
	cl_publicationsDB.Save();
	cl_copiesDB.Save();
	//
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

	auto index = cl_loginDB.FindByAll(cl_authPriveleges);
	if (index < 0)
	{
		throw MyException("Видимо, что-то пошло не так");
	}

	if (cl_loginDB[index].InputNewPassword())
	{
		cl_loginDB.SomethingIsChanged();
	}

	cl_authPriveleges = cl_loginDB[index];
	cl_loginDB.Save();
}
*/