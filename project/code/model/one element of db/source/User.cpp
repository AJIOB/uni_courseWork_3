#include "../headers/User.h"
#include "../../dbs/headers/UserDBClass.h"

void OneElementOf::User::BWrite(const bString& bInfo, strPos& it)
{
	DefaultID buflogin(bInfo, it);
	User buffer(*this);
	buffer.cl_login = buflogin;
	buffer.cl_password = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_name = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_surname = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_fatherName = BStringIO::ReadBInfo<std::string>(bInfo, it);

	(*this) = buffer;
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
	cl_parentDB = that.cl_parentDB;
	cl_login = that.cl_login;
	cl_password= that.cl_password;
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

bool OneElementOf::User::CheckPassword(const std::string& password) const
{
	return (password == cl_password);
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

bool OneElementOf::User::InputNewPassword()
{
	std::string currPwd = Stream::Getpass("Введите старый пароль");

	if (currPwd != cl_password)
	{
		OutputConsole("Извините, вы ввели неправильный старый пароль. Отмена смены пароля.");
		return false;
	}

	while (true)
	{
		std::string buffTry1 = Stream::Getpass("Введите новый пароль");
		std::string buffTry2 = Stream::Getpass("Повторите новый пароль");

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
	OutputConsole("Новый пароль: \"" + cl_password + "\"");
}

std::string OneElementOf::User::InputNewString(const std::string& textToShow)
{
	do 
	{
		OutputConsole(textToShow);
		std::string buff = Stream::Input<std::string>();

		OutputConsole("Вы ввели: " + buff);

		if (Stream::GetOnlyYN("Всё введено корректно?") == 'Y')
		{
			return buff;
		}

		ClearConsole();
		OutputConsole("Пожалуйста, повторите ввод");
	} while (true);
}

bString OneElementOf::User::BRead() const
{
	return (cl_login.BRead() + BStringIO::MakeBString(cl_password) + BStringIO::MakeBString(cl_name) + BStringIO::MakeBString(cl_surname) + BStringIO::MakeBString(cl_fatherName));
}

void OneElementOf::User::InputAuthInfoFromConsole()
{
	//todo
	OutputConsole("Введите логин:");
	cl_login.SetID(Stream::Input<uli>());
	cl_password = Stream::Getpass("Введите пароль:");
}

bool OneElementOf::User::EqualByAll(const User& that) const
{
	return (EqualByLogin(that) && EqualByName(that) && EqualBySurname(that) && EqualByFatherName(that));	
}

bool OneElementOf::User::EqualByLogin(const User& that) const
{
	return (this->cl_login == that.cl_login);
}

bool OneElementOf::User::EqualByPassword(const User& that) const
{
	return (this->cl_password == that.cl_password);
}

bool OneElementOf::User::EqualByAuth(const User& that) const
{
	return (EqualByLogin(that) && EqualByPassword(that));
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

bool OneElementOf::User::operator<(const User& that) const
{
	return (cl_login.GetID() < that.cl_login.GetID());
}

bool OneElementOf::User::operator>(const User& that) const
{
	return (cl_login.GetID() > that.cl_login.GetID());
}

bool OneElementOf::User::UpdateMe()
{
	//todo

	ClearConsole();
	bool isUpdated = false;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть элемент" << std::endl;
		std::cout << "2) Сбросить пароль" << std::endl;
		std::cout << "3) Изменить права доступа" << std::endl;
		std::cout << "4) Изменить фамилию" << std::endl;
		std::cout << "5) Изменить имя" << std::endl;
		std::cout << "6) Изменить отчество" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			std::cout << *this << std::endl;
			break;
		case '2':
			this->ResetPassword();
			isUpdated = true;
			break;
		case '3':
			this->InputNewPrivelege();
			isUpdated = true;
			break;
		case '4':
			cl_surname = InputNewString("Введите новую фамилию");
			isUpdated = true;
			break;
		case '5':
			cl_name = InputNewString("Введите новое имя");
			isUpdated = true;
			break;
		case '6':
			cl_fatherName = InputNewString("Введите новое отчество");
			isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

std::ostream& OneElementOf::operator<<(std::ostream& s, const User& that)
{
	s << that.cl_login << std::endl;

	s << "Фамилия: " << that.cl_surname << std::endl;
	s << "Имя: " << that.cl_name << std::endl;
	s << "Отчество: " << that.cl_fatherName << std::endl;

	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, User& that)
{
	User buff(that);

	if (buff.cl_parentDB)
	{
		buff.cl_login.SetID(buff.cl_parentDB->GetNewID());
	}
	else
	{
		buff.cl_login.SetID(1);
	}

	OutputConsole("Введите права доступа пользователя: ");
	buff.cl_login.InputNewType();

	//buff.cl_password = Stream::Getpass("Введите пароль для нового пользователя");
	buff.ResetPassword();

	OutputConsole("Введите фамилию:");
	Stream::Input(buff.cl_surname);
	OutputConsole("Введите имя:");
	Stream::Input(buff.cl_name);
	OutputConsole("Введите отчество:");
	Stream::Input(buff.cl_fatherName);

	that = buff;

	return s;
}

