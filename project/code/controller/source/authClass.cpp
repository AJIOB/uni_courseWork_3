#include "../headers/authClass.h"

AuthClass::AuthClass() : cl_loginDB(new AuthDBClass()), cl_currentUser(cl_loginDB)
{
	//loginDB = new AuthDBClass();
	cl_isGetDBbyExternal = false;
}

AuthClass::AuthClass(AuthDBClass* loginDBnew) : cl_currentUser(loginDBnew)
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
