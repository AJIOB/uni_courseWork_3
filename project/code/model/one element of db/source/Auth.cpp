#include "../headers/Auth.h"

void OneElementOf::Auth::BWrite(const std::string& bInfo, strPos& it)
{
	DefaultID <AJIOBTypes::PrivelegeType> buflogin(bInfo, it);
	login = buflogin;
	password = BStringIO::ReadBInfo<std::string>(bInfo, it);
}

OneElementOf::Auth::Auth():login()
{
	//privelege = PrivelegeType::none;
}

OneElementOf::Auth::Auth(const std::string& bInfo, strPos& it)
{
	BWrite(bInfo, it);
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
	return (login.BRead() + BStringIO::GetBString(password));
}

std::ostream& OneElementOf::operator<<(std::ostream& s, const Auth& that)
{
	s << that.login << std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Auth& that)
{
	s >> that.login;

	while (true)
	{
		std::string buffTry1 = getpass("Введите пароль");
		std::string buffTry2 = getpass("Повторите пароль");

		if (buffTry1 == buffTry2)
		{
			that.password = buffTry1;
			break;
		}

		OutputInfo("Введенные пароли не совпадают. Пожалуйста, повторите ввод");
	}
	return s;
}
