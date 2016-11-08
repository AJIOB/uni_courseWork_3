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
AuthClass::AuthClass() : loginDB(new LoginDBClass()), CurrentUser(loginDB)
{
	//loginDB = new LoginDBClass();
	isGetDBbyExternal = false;
}

AuthClass::AuthClass(LoginDBClass* loginDBnew) : CurrentUser(loginDBnew)
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

OneElementOf::Auth AuthClass::run()
{
	OneElementOf::Auth currentLoginPassword(this);
	currentLoginPassword.InputAuthFromConsole();

	int index = loginDB->Find(currentLoginPassword);

	if (index < 0)
	{
		throw NoLoginException();
	}

	try
	{
		return loginDB->GetElement(index);
	}
	catch(std::out_of_range& e)
	{
		OutputConsole(e.what());
		OutputLog(e.what());
		return OneElementOf::Auth(this);
	}	
}
