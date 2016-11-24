#include "../headers/authClass.h"

AuthClass::AuthClass() : cl_dbWithAuthInfo(new UserDBClass())/*, cl_currentUser(cl_dbWithAuthInfo)*/
{
	//loginDB = new AuthDBClass();
	cl_isGetDBbyExternal = false;
}

AuthClass::AuthClass(UserDBClass* loginDBnew) /*: cl_currentUser(loginDBnew)*/
{
	cl_dbWithAuthInfo = loginDBnew;
	cl_isGetDBbyExternal = true;
}

AuthClass::~AuthClass()
{
	if (!cl_isGetDBbyExternal && cl_dbWithAuthInfo)
	{
		delete cl_dbWithAuthInfo;
	}
}

DefaultID AuthClass::run()
{
	//todo: remake

	OneElementOf::User currentLoginPassword(this);
	currentLoginPassword.InputAuthInfoFromConsole();

	int index = cl_dbWithAuthInfo->FindByAuthInfo(currentLoginPassword);

	if (index < 0)
	{
		throw NoLoginException();
	}

	try
	{
		return cl_dbWithAuthInfo->GetElement(index).GetLogin();
	}
	catch(std::out_of_range& e)
	{
		OutputConsole(e.what());
		OutputLog(e.what());
		return DefaultID();
	}	
}
