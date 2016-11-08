#include "../headers/Auth.h"

void OneElementOf::Auth::BWrite(const std::string& bInfo, strPos& it)
{
	DefaultID <AJIOBTypes::PrivelegeType> buflogin(bInfo, it);
	cl_login = buflogin;
	cl_password = BStringIO::ReadBInfo<std::string>(bInfo, it);
}

OneElementOf::Auth::Auth(void* parentDB):cl_login()
{
	cl_parentDB = reinterpret_cast<LoginDBClass*> (parentDB);
}

OneElementOf::Auth::Auth(const Auth& that)
{
	(*this) = that;
}

OneElementOf::Auth::Auth(const std::string& bInfo, strPos& it, void* parentDB)
{
	cl_parentDB = reinterpret_cast<LoginDBClass*> (parentDB);
	BWrite(bInfo, it);
}

OneElementOf::Auth::~Auth()
{
	//cl_login.clear();
	cl_password.clear();
}

OneElementOf::Auth& OneElementOf::Auth::operator=(const Auth& that)
{
	cl_parentDB  =that.cl_parentDB;
	cl_login = that.cl_login;
	cl_password = that.cl_password;
	return (*this);
}

DefaultID<AJIOBTypes::PrivelegeType> OneElementOf::Auth::GetLogin() const
{
	return this->cl_login;
}
/*
void OneElementOf::Auth::SetLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin)
{
	this->cl_login = newLogin;
}*/

void OneElementOf::Auth::InputNewPrivelege()
{
	Auth buffer(*this);
	do
	{
		buffer.cl_login.InputNewType();
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
}

bool OneElementOf::Auth::InputNewPassword()
{
	std::string currPwd = getpass("Введите старый пароль");

	if (currPwd != cl_password)
	{
		OutputConsole("Извините, вы ввели неправильный старый пароль. Отмена смены пароля.");
		return false;
	}

	while (true)
	{
		std::string buffTry1 = getpass("Введите новый пароль");
		std::string buffTry2 = getpass("Повторите новый пароль");

		if (buffTry1 == buffTry2)
		{
			cl_password = buffTry1;
			break;
		}

		OutputConsole("Введенные пароли не совпадают. Пожалуйста, повторите ввод");
	}

	return true;
}

void OneElementOf::Auth::SetPassword(const std::string& newPassword)
{
	this->cl_password = newPassword;
}

void OneElementOf::Auth::ResetPassword()
{
	cl_password = AJIOBStringFuncs::IntToString(cl_login.GetID());
	OutputConsole("Новый пароль: " + cl_password);
}

std::string OneElementOf::Auth::BRead()
{
	return (cl_login.BRead() + BStringIO::GetBString(cl_password));
}

void OneElementOf::Auth::InputAuthFromConsole()
{
	OutputConsole("Введите логин:");
	cl_login.SetID(Stream::Input<uli>());
	cl_password = getpass("Введите пароль:");
}

bool OneElementOf::Auth::EqualByAll(const Auth& that) const
{
	return (EqualByLogin(that) && (cl_password == that.cl_password));
}

bool OneElementOf::Auth::EqualByLogin(const Auth& that) const
{
	return (this->cl_login == that.cl_login);
}

bool OneElementOf::Auth::operator==(const Auth& that) const
{
	return EqualByAll(that);
}

std::ostream& OneElementOf::operator<<(std::ostream& s, const Auth& that)
{
	s << that.cl_login << std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Auth& that)
{
	s >> that.cl_login;

	while (true)
	{
		std::string buffTry1 = getpass("Введите пароль");
		std::string buffTry2 = getpass("Повторите пароль");

		if (buffTry1 == buffTry2)
		{
			that.cl_password = buffTry1;
			break;
		}

		OutputConsole("Введенные пароли не совпадают. Пожалуйста, повторите ввод");
	}
	return s;
}

