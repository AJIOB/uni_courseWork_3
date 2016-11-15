#pragma once
#include <string>

#include "../../other/templates/DefaultID.h"
#include "../../enums/PrivelegeType.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../other/headers/StringFuncs.h"


namespace OneElementOf
{
	class Auth;
}

class LoginDBClass;

class OneElementOf::Auth
{
	friend LoginDBClass;
	LoginDBClass* cl_parentDB;

	DefaultID <AJIOBTypes::PrivelegeType::PrivelegeType> cl_login;
	std::string cl_password;

	void BWrite(const std::string& bInfo, strPos& it);
public:
	Auth(void* parentDB);
	Auth(const Auth& that);
	Auth(const std::string& bInfo, strPos& it, void* parentDB);
	~Auth();

	Auth& operator=(const Auth& that);
	
	DefaultID<AJIOBTypes::PrivelegeType::PrivelegeType> GetLogin() const;
		
	//void SetLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
	void InputNewPrivelege();
	bool InputNewPassword();
	void SetPassword(const std::string& newPassword);
	void ResetPassword();

	std::string BRead();

	friend std::ostream& operator<< (std::ostream& s, const Auth& that);
	friend std::istream& operator>> (std::istream& s, Auth& that);

	void InputAuthFromConsole();

	bool EqualByAll(const Auth& that) const;
	bool EqualByLogin(const Auth& that) const;

	bool operator==(const Auth& that) const;
};