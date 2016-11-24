#pragma once

#include "../../view/headers/view.h"
#include "../../model/exceptions/AllExceptions.h"
#include "../headers/authClass.h"

//#include "../../model/dbs/headers/AuthDBClass.h"
#include "../../model/dbs/headers/CountryDBClass.h"
#include "../../model/dbs/headers/PublicationDBClass.h"
#include "../../model/dbs/headers/CopiesDBClass.h"
#include "../../model/dbs/headers/UserDBClass.h"



class AJIOB_DBSystem
{
	//AuthDBClass cl_loginDB;
	CountryDBClass cl_countriesDB;
	PublicationDBClass cl_publicationsDB;
	CopiesDBClass cl_copiesDB;
	UserDBClass cl_userDB;

	//

	DefaultID cl_loggedUserID;

	//сам процесс авторизации
	DefaultID Auth();
	
	bool SaveAllChanges();

	void ManageYourProfile();
	//void ChangeYourPassword();

public:
	AJIOB_DBSystem();
	~AJIOB_DBSystem();

	AJIOBTypes::PrivelegeType::PrivelegeType RunLoginProcess();
	bool ExecuteQuery(const std::string& query, bString& result);
};
