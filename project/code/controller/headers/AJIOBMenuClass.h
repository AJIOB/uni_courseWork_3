#pragma once

#include "../../model/dbs/headers/LoginDBClass.h"
#include "../../view/headers/view.h"
#include "../../other/headers/NoLoginException.h"
#include "../headers/authClass.h"

class AJIOBMenuClass
{
	LoginDBClass cl_loginDB;
	//

	DefaultID<AJIOBTypes::PrivelegeType> Auth() const;
	int LoginSuccessfully(DefaultID<AJIOBTypes::PrivelegeType> loggedUserID);

	void WithLoginDB();
	void WithBooksDBs();
	void WithClientDB();

	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	//
public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run();
};
