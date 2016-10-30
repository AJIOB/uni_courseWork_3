#include "Auth.h"

void OneElementOf::Auth::BWrite(const std::string& bInfo)
{
	strPos it = 0;

	password = BStringIO::ReadBInfo<std::string>(bInfo, it);
}

OneElementOf::Auth::Auth():login()
{
	//privelege = PrivelegeType::none;
}

OneElementOf::Auth::Auth(const std::string& bInfo)
{
	BWrite(bInfo);
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

std::string OneElementOf::Auth::BRead()
{
	//std::string s;
	return (login.BRead() + BStringIO::GetBString(password));
}
