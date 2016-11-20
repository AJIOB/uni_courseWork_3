#include "../headers/User.h"

void OneElementOf::User::BWrite(const bString& bInfo, strPos& it)
{
	DefaultID buflogin(bInfo, it);
	User buffer(*this);
	buffer.cl_login = buflogin;
	buffer.cl_name = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_surname = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_fatherName = BStringIO::ReadBInfo<std::string>(bInfo, it);

	(*this) = buffer;
	//return (cl_login.BRead() + BStringIO::MakeBString(cl_name) + BStringIO::MakeBString(cl_surname) + BStringIO::MakeBString(cl_fatherName));
}

OneElementOf::User::User(void* parentDB):cl_login()
{
	cl_parentDB = reinterpret_cast<UserDBClass*> (parentDB);
}

OneElementOf::User::User(const User& that)
{
	(*this) = that;
}

OneElementOf::User::User(const bString& bInfo, strPos& it, void* parentDB)
{
	cl_parentDB = reinterpret_cast<UserDBClass*> (parentDB);
	BWrite(bInfo, it);
}

OneElementOf::User::~User()
{
}

OneElementOf::User& OneElementOf::User::operator=(const User& that)
{
	cl_parentDB  =that.cl_parentDB;
	cl_login = that.cl_login;
	cl_name = that.cl_name;
	cl_surname = that.cl_surname;
	cl_fatherName = that.cl_fatherName;
	return (*this);
}

DefaultID OneElementOf::User::GetLogin() const
{
	return this->cl_login;
}

std::string OneElementOf::User::GetName() const
{
	return cl_name;
}

std::string OneElementOf::User::GetSurname() const
{
	return cl_surname;
}

std::string OneElementOf::User::GetFatherName() const
{
	return cl_fatherName;
}

/*
void OneElementOf::User::SetLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin)
{
	this->cl_login = newLogin;
}*/

void OneElementOf::User::InputNewPrivelege()
{
	User buffer(*this);
	do
	{
		buffer.cl_login.InputNewType();
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
}
/*
bool OneElementOf::User::InputNewPassword()
{
	std::string currPwd = Stream::getpass("Введите старый пароль");

	if (currPwd != cl_password)
	{
		OutputConsole("Извините, вы ввели неправильный старый пароль. Отмена смены пароля.");
		return false;
	}

	while (true)
	{
		std::string buffTry1 = Stream::getpass("Введите новый пароль");
		std::string buffTry2 = Stream::getpass("Повторите новый пароль");

		if (buffTry1 == buffTry2)
		{
			cl_password = buffTry1;
			break;
		}

		OutputConsole("Введенные пароли не совпадают. Пожалуйста, повторите ввод");
	}

	return true;
}

void OneElementOf::User::SetPassword(const std::string& newPassword)
{
	this->cl_password = newPassword;
}

void OneElementOf::User::ResetPassword()
{
	cl_password = AJIOBStringFuncs::IntToString(cl_login.GetID());
	OutputConsole("Новый пароль: " + cl_password);
}
*/
bString OneElementOf::User::BRead() const
{
	return (cl_login.BRead() + BStringIO::MakeBString(cl_name) + BStringIO::MakeBString(cl_surname) + BStringIO::MakeBString(cl_fatherName));
}

bool OneElementOf::User::EqualByAll(const User& that) const
{
	return (EqualByLogin(that) && EqualByName(that) && EqualBySurname(that) && EqualByFatherName(that));	
}

bool OneElementOf::User::EqualByLogin(const User& that) const
{
	return (this->cl_login == that.cl_login);
}

bool OneElementOf::User::EqualByName(const User& that) const
{
	return (cl_name == that.cl_name);
}

bool OneElementOf::User::EqualBySurname(const User& that) const
{
	return (cl_surname == that.cl_surname);
}

bool OneElementOf::User::EqualByFatherName(const User& that) const
{
	return (cl_fatherName == that.cl_fatherName);
}

bool OneElementOf::User::operator==(const User& that) const
{
	return EqualByAll(that);
}

std::ostream& OneElementOf::operator<<(std::ostream& s, const User& that)
{
	s << that.cl_login << std::endl;
	s << "Имя: " << that.cl_name << std::endl;
	s << "Фамилия: " << that.cl_surname << std::endl;
	s << "Отчество: " << that.cl_fatherName << std::endl;

	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, User& that)
{
	User buff(that);

	s >> buff.cl_login;

	OutputConsole("Введите имя:");
	Stream::Input(buff.cl_name);
	OutputConsole("Введите фамилию:");
	Stream::Input(buff.cl_surname);
	OutputConsole("Введите отчество:");
	Stream::Input(buff.cl_fatherName);

	that = buff;

	return s;
}

