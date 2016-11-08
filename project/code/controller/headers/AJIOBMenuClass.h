#pragma once

#include "../../model/dbs/headers/LoginDBClass.h"
#include "../../view/headers/view.h"
#include "../../model/exceptions/AllExceptions.h"
#include "../headers/authClass.h"
#include "../../model/dbs/headers/PublisherDBClass.h"
#include "../../model/dbs/headers/CountryDBClass.h"

class AJIOBMenuClass
{
	LoginDBClass cl_loginDB;
	//PublisherDBClass cl_publishersDB;
	CountryDBClass cl_countriesDB;

	//

	OneElementOf::Auth cl_loggedUser;

	OneElementOf::Auth Auth();
	int LoginSuccessfully();

	void WithLoginDB();
	void WithPublisherDB();
	void WithCountryDB();

	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	//
	void SaveAllChanges();

	void ManageYourProfile();
	void ChangeYourPassword();

public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run();
};
