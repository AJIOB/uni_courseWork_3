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
AuthClass::AuthClass() : cl_loginDB(new LoginDBClass()), cl_currentUser(cl_loginDB)
{
	//loginDB = new LoginDBClass();
	cl_isGetDBbyExternal = false;
}

AuthClass::AuthClass(LoginDBClass* loginDBnew) : cl_currentUser(loginDBnew)
{
	cl_loginDB = loginDBnew;
	cl_isGetDBbyExternal = true;
}

AuthClass::~AuthClass()
{
	if (!cl_isGetDBbyExternal && cl_loginDB)
	{
		delete cl_loginDB;
	}
}

OneElementOf::Auth AuthClass::run()
{
	OneElementOf::Auth currentLoginPassword(this);
	currentLoginPassword.InputAuthFromConsole();

	int index = cl_loginDB->Find(currentLoginPassword);

	if (index < 0)
	{
		throw NoLoginException();
	}

	try
	{
		return cl_loginDB->GetElement(index);
	}
	catch(std::out_of_range& e)
	{
		OutputConsole(e.what());
		OutputLog(e.what());
		return OneElementOf::Auth(this);
	}	
}
