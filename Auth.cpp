#include "Auth.h"

OneElementOf::Auth::Auth():login()
{
	//privelege = PrivelegeType::none;
}

OneElementOf::Auth::~Auth()
{
	//login.clear();
	password.clear();
}

DefaultID<AJIOBTypes::PrivelegeType> OneElementOf::Auth::getLogin() const
{
	return this->login;
}

void OneElementOf::Auth::setLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin)
{
	this->login = newLogin;
}

void OneElementOf::Auth::setPassword(const std::string& newPassword)
{
	this->password = newPassword;
}
