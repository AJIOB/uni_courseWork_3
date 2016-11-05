#include "../headers/authClass.h"

/*
void AuthClass::AuthProcessing()
{
	OneElementOf::Auth currentLogin;
	currentLogin;
	OutputConsole("¬ведите логин:\n");
	currentLogin.setPassword(getpass("¬ведите пароль:"));
}
*/
AuthClass::AuthClass()
{
	loginDB = new LoginDBClass();
	isGetDBbyExternal = false;
}

AuthClass::AuthClass(const LoginDBClass* loginDBnew)
{
	loginDB = loginDBnew;
	isGetDBbyExternal = true;
}

AuthClass::~AuthClass()
{
	if (!isGetDBbyExternal && loginDB)
	{
		delete loginDB;
	}
}

DefaultID<AJIOBTypes::PrivelegeType> AuthClass::run() const
{
	OneElementOf::Auth currentLoginPassword;
	currentLoginPassword.InputAuthFromConsole();

	int index = loginDB->Find(currentLoginPassword);

	if (index < 0)
	{
		throw NoLoginException();
	}

	try
	{
		return loginDB->Get(index).GetLogin();
	}
	catch(std::out_of_range& e)
	{
		OutputConsole(e.what());
		OutputLog(e.what());
		return DefaultID<AJIOBTypes::PrivelegeType>();
	}	
}
