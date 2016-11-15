#pragma once

#include "../../view/headers/view.h"
#include "../../model/exceptions/AllExceptions.h"
#include "../headers/authClass.h"

#include "../../model/dbs/headers/LoginDBClass.h"
#include "../../model/dbs/headers/CountryDBClass.h"
#include "../../model/dbs/headers/PublicationDBClass.h"


class AJIOBMenuClass
{
	LoginDBClass cl_loginDB;
	CountryDBClass cl_countriesDB;
	PublicationDBClass cl_publicationsDB;

	//

	OneElementOf::Auth cl_loggedUser;

	OneElementOf::Auth Auth();
	int LoginSuccessfully();

	void WithLoginDB();
	void WithCountryDB();
	void WithPublicationsDB();

	//

	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	
	void SaveAllChanges();

	void ManageYourProfile();
	void ChangeYourPassword();

public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run();
};
