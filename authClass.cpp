#include "authClass.h"

void AuthClass::AuthProcessing()
{
	OneElementOf::Auth currentLogin;
	std::cout << "������� �����:\n";
	//currentLogin.setLogin(Input<DefaultID<AJIOBTypes::PrivelegeType>>());
	currentLogin.setPassword(getpass("������� ������:"));
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
