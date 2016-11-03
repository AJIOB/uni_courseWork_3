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
	
		DefaultID<AJIOBTypes::PrivelegeType> getLogin() const;
		
		void setLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
		void setPassword(const std::string& newPassword);

		std::string BRead();

		friend std::ostream& operator<< (std::ostream& s, const Auth& that);
		friend std::istream& operator>> (std::istream& s, Auth& that);
	};
}