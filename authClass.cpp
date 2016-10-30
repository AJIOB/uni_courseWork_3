#include "authClass.h"

void AuthClass::AuthProcessing()
{
	OneElementOf::Auth currentLogin;
	std::cout << "¬ведите логин:\n";
	//currentLogin.setLogin(Input<DefaultID<AJIOBTypes::PrivelegeType>>());
	currentLogin.setPassword(getpass("¬ведите пароль:"));
}

AuthClass::AuthClass(): loginDB(wayToLoginDB)
{
	
}

AuthClass::~AuthClass()
{
	
}

DefaultID<AJIOBTypes::PrivelegeType> AuthClass::run()
{
	//
	//AuthProcessing();

	return DefaultID<AJIOBTypes::PrivelegeType>();
}
