#pragma once
#include <string>

#include "DefaultID.h"
#include "PrivelegeType.h"

namespace OneElementOf
{
	class Auth
	{
		DefaultID <AJIOBTypes::PrivelegeType> login;
		std::string password;
	public:
		Auth();
		~Auth();
	
		DefaultID<AJIOBTypes::PrivelegeType> getLogin() const;
		
		void setLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
		void setPassword(const std::string& newPassword);
	
		/*
		//PrivelegeType getPrivelege() const;
	/*
	private:
		//PrivelegeType privelege;
	
		friend class AuthClass;*/
	};
}