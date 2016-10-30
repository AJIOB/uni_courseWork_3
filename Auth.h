#pragma once
#include <string>

#include "DefaultID.h"
#include "PrivelegeType.h"
#include "BStringIO.h"

namespace OneElementOf
{
	class Auth
	{
		DefaultID <AJIOBTypes::PrivelegeType> login;
		std::string password;

		void BWrite(const std::string& bInfo);
	public:
		Auth();
		Auth(const std::string& bInfo);
		~Auth();
	
		DefaultID<AJIOBTypes::PrivelegeType> getLogin() const;
		
		void setLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
		void setPassword(const std::string& newPassword);

		std::string BRead();

		/*
		//PrivelegeType getPrivelege() const;
	/*
	private:
		//PrivelegeType privelege;
	
		friend class AuthClass;*/
	};
}