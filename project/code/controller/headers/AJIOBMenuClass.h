#pragma once

#include "../../model/dbs/headers/LoginDBClass.h"
#include "../../view/headers/view.h"
//#include "../../model/other/templates/DefaultID.h"
//#include "../../model/enums/PrivelegeType.h"

class AJIOBMenuClass
{
	LoginDBClass cl_loginDB;


	void WithLoginDB();
	void WithBooksDBs();
	void WithClientDB();

public:	//for debugging
	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	//
public:
	AJIOBMenuClass();
	~AJIOBMenuClass();

	int run(DefaultID<AJIOBTypes::PrivelegeType> loggedUser);
};
