#pragma once
#include <string>

#include "../../other/headers/DefaultID.h"
#include "../../enums/PrivelegeType.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../other/headers/StringFuncs.h"


namespace OneElementOf
{
	class Auth;
}

class AuthDBClass;

class OneElementOf::Auth
{
	friend AuthDBClass;
	AuthDBClass* cl_parentDB;

	DefaultID cl_login;
	std::string cl_password;

	void BWrite(const bString& bInfo, strPos& it);
public:
	Auth(void* parentDB);
	Auth(const Auth& that);
	Auth(const bString& bInfo, strPos& it, void* parentDB);
	~Auth();

	Auth& operator=(const Auth& that);
	
	DefaultID GetLogin() const;
		
	//void SetLogin(const DefaultID& newLogin);
	void InputNewPrivelege();
	bool InputNewPassword();
	void SetPassword(const std::string& newPassword);
	void ResetPassword();

	bString BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Auth& that);
	friend std::istream& operator>> (std::istream& s, Auth& that);

	void InputAuthFromConsole();

	bool EqualByAll(const Auth& that) const;
	bool EqualByLogin(const Auth& that) const;

	bool operator==(const Auth& that) const;
};