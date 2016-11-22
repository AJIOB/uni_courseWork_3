#include "../headers/AJIOB_DBSystem.h"


OneElementOf::Auth AJIOB_DBSystem::Auth()
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
/*
int AJIOB_DBSystem::LoginSuccessfully()
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
*//*
void AJIOB_DBSystem::WithLoginDB()
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

void AJIOB_DBSystem::WithCountryDB()
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

void AJIOB_DBSystem::WithPublicationsDB()
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
			cl_publicationsDB.Show();
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

void AJIOB_DBSystem::WithCopiesDB()
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
			cl_copiesDB.Show();
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

bool AJIOB_DBSystem::SaveAllChanges()
{
	if (
		cl_loginDB.Save() ||
		cl_countriesDB.Save() ||
		cl_publicationsDB.Save() ||
		cl_copiesDB.Save() ||
		cl_userDB.Save()
		)
	{
		return true;
	}

	return false;


	//todo: add dbs
}

void AJIOB_DBSystem::ManageYourProfile()
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
			return;/*
		case '1':
			ChangeYourPassword();
			break;*/
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}
/*
void AJIOB_DBSystem::ChangeYourPassword()
{
	ClearConsole();

	auto index = cl_loginDB.Find(cl_loggedUserID);
	if (index < 0)
	{
		throw MyException("Видимо, что-то пошло не так");
	}

	if (cl_loginDB[index].InputNewPassword())
	{
		cl_loginDB.SomethingIsChanged();
	}

	cl_loggedUserID = cl_loginDB[index];
	cl_loginDB.Save();
}*/

AJIOB_DBSystem::AJIOB_DBSystem() :
	cl_loginDB(), cl_countriesDB(), cl_publicationsDB(&cl_countriesDB/*, &cl_copiesDB*/), cl_copiesDB(&cl_publicationsDB)
{

}

AJIOB_DBSystem::~AJIOB_DBSystem()
{
	SaveAllChanges();
}

AJIOBTypes::PrivelegeType::PrivelegeType AJIOB_DBSystem::RunLoginProcess()
{
	AuthClass localAuth(&cl_loginDB);
	OneElementOf::Auth loggedAuthElement(&cl_loginDB);

	do
	{
		try
		{
			loggedAuthElement = localAuth.run();

			//todo поиск по другой базе данных (там где есть права доступа)

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

	//todo: поправить права доступа

	cl_loggedUserID = loggedAuthElement.GetLogin();

	return cl_loggedUserID.GetType();
}

bool AJIOB_DBSystem::ExecuteQuery(const std::string& query, bString& result)
{
	if (cl_loggedUserID == DefaultID())
	{
		return false;
	}

	result = "";

	//select DB to execute query
	std::string whatDB;
	std::string rightPart;

	AJIOBStringFuncs::BreakStringTo2Strings(query, whatDB, rightPart, '.');

	//todo: обработка других команд

	if (whatDB == "countries")
	{
		return cl_countriesDB.ExecuteQuery(rightPart, result);
	}
	
	if (whatDB == "auth")
	{
		return cl_loginDB.ExecuteQuery(rightPart, result);
	}

	if (whatDB == "publications")
	{
		return cl_publicationsDB.ExecuteQuery(rightPart, result);
	}

	if (whatDB == "bookcopies")
	{
		return cl_copiesDB.ExecuteQuery(rightPart, result);
	}

	if (whatDB == "users")
	{
		return cl_userDB.ExecuteQuery(rightPart, result);
	}

	if (whatDB == "saveall")
	{
		return SaveAllChanges();
	}

	//todo: add new bases

	return false;
}
