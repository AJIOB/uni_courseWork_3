#pragma once

#include "Auth.h"
#include "WorkWithStreams.h"

class AJIOBMenuClass
{
	void WithLoginDB();
	void WithBooksDBs();
	void WithClientDB();


public:	//for debugging
	void AdminMenu();
	void WorkerMenu();
	void ClientMenu();
	//
public:

	int run(DefaultID<AJIOBTypes::PrivelegeType> loggedUser);
};
