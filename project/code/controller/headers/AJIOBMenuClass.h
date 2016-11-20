#pragma once
/*
#include "../../view/headers/view.h"
#include "../../model/exceptions/AllExceptions.h"*/
#include "../headers/authClass.h"
#include "AJIOB_DBSystem.h"

/*
#include "../../model/dbs/headers/AuthDBClass.h"
#include "../../model/dbs/headers/CountryDBClass.h"
#include "../../model/dbs/headers/PublicationDBClass.h"
#include "../../model/dbs/headers/CopiesDBClass.h"
#include "../../model/dbs/headers/UserDBClass.h"
*/

class AJIOBMenuClass
{
	AJIOB_DBSystem cl_localCopyOfDBSys;

	AJIOBTypes::PrivelegeType::PrivelegeType cl_authPriveleges;
	
	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();

	void SelectFunction(const std::string& dbName);

	void Add(const std::string& dbName);
	void Show(const std::string& dbName);
	void Update(const std::string& dbName);
	void Delete(const std::string& dbName);

	void SaveAll();

public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run();
};

/*
	OneElementOf::Auth Auth();
	int LoginSuccessfully();

	void WithLoginDB();
	void WithCountryDB();
	void WithPublicationsDB();
	void WithCopiesDB();

	//

	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	
	void SaveAllChanges();

	void ManageYourProfile();
	void ChangeYourPassword();
	/*/