#include "../headers/AJIOB_DBSystem.h"


DefaultID AJIOB_DBSystem::Auth()
{
	AuthClass localAuth(&cl_userDB);
	//OneElementOf::Auth loggedAuthElement(&cl_loginDB);
	DefaultID loggedID;

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
	while (Stream::GetOnlyYN("Желаете повторить ввод?") == 'Y');

	return loggedID;
}

bool AJIOB_DBSystem::SaveAllChanges()
{
	bool result = cl_countriesDB.Save();
	result = cl_publicationsDB.Save() || result;
	result = cl_copiesDB.Save() || result;
	result = cl_userDB.Save() || result;

	//todo: add dbs

	return result;
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
			cl_userDB.Save();
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

	auto index = cl_loginDB.FindByAll(cl_loggedUserID);
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
	cl_countriesDB(), cl_publicationsDB(&cl_countriesDB/*, &cl_copiesDB*/), cl_copiesDB(&cl_publicationsDB)
{

}

AJIOB_DBSystem::~AJIOB_DBSystem()
{
	SaveAllChanges();
}

AJIOBTypes::PrivelegeType::PrivelegeType AJIOB_DBSystem::RunLoginProcess()
{
	cl_loggedUserID = Auth();

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
	/*
	if (whatDB == "auth")
	{
		return cl_loginDB.ExecuteQuery(rightPart, result);
	}*/

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
