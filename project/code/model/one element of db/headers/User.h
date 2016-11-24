#pragma once
#include <string>

#include "../../other/headers/DefaultID.h"
#include "../../enums/PrivelegeType.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../other/headers/StringFuncs.h"
//#include "Auth.h"


namespace OneElementOf
{
	class User;
}

class UserDBClass;

class OneElementOf::User
{
	//friend UserDBClass;
	UserDBClass* cl_parentDB;
	
	DefaultID cl_login;
	std::string cl_password;

	//OneElementOf::Auth cl_auth_field;

	std::string cl_name;
	std::string cl_surname;
	std::string cl_fatherName;

	void BWrite(const bString& bInfo, strPos& it);
public:
	User(void* parentDB = nullptr);
	User(const User& that);
	User(const bString& bInfo, strPos& it, void* parentDB = nullptr);
	~User();

	User& operator=(const User& that);
	
	DefaultID GetLogin() const;
	std::string GetName() const;
	std::string GetSurname() const;
	std::string GetFatherName() const;
	bool CheckPassword(const std::string& password) const;
		
	//void SetLogin(const DefaultID& newLogin);
	void InputNewPrivelege();
	bool InputNewPassword();
	void SetPassword(const std::string& newPassword);
	void ResetPassword();
	static std::string InputNewString(const std::string& textToShow);
	
	bString BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const User& that);
	friend std::istream& operator>> (std::istream& s, User& that);

	void InputAuthInfoFromConsole();

	bool EqualByAll(const User& that) const;
	bool EqualByLogin(const User& that) const;
	bool EqualByPassword(const User& that) const;
	bool EqualByAuth(const User& that) const;
	bool EqualByName(const User& that) const;
	bool EqualBySurname(const User& that) const;
	bool EqualByFatherName(const User& that) const;

	bool operator==(const User& that) const;
	bool operator<(const User& that) const;
	bool operator>(const User& that) const;

	bool UpdateMe();
};

template <>
inline OneElementOf::User BStringIO::ReadBInfo<OneElementOf::User>(const bString& str, strPos& iterator)
{
	return OneElementOf::User(str, iterator, nullptr);
}

template <>
inline bString BStringIO::MakeBString<OneElementOf::User>(const OneElementOf::User& info)
{
	return info.BRead();
}