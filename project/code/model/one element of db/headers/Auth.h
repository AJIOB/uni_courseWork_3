#pragma once
#include <string>

#include "../../other/templates/DefaultID.h"
#include "../../enums/PrivelegeType.h"
#include "../../binary input&output/templates/BStringIO.h"


namespace OneElementOf
{
	class Auth
	{
		DefaultID <AJIOBTypes::PrivelegeType> login;
		std::string password;

		void BWrite(const std::string& bInfo, strPos& it);
	public:
		Auth();
		Auth(const std::string& bInfo, strPos& it);
		~Auth();
	
		DefaultID<AJIOBTypes::PrivelegeType> GetLogin() const;
		
		void SetLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
		void SetPassword(const std::string& newPassword);

		std::string BRead();

		friend std::ostream& operator<< (std::ostream& s, const Auth& that);
		friend std::istream& operator>> (std::istream& s, Auth& that);

		void InputAuthFromConsole();

		bool EqualByAll(const Auth& that) const;
		bool EqualByLogin(const Auth& that) const;

		bool operator==(const Auth& that) const;
	};
}