#include "MyLibrary.h"

//#include "ExternalLib.h"


int defaultFunction()
{
	//testing
	/*
	CryptedDB<int> qwe(std::string("test"));

	std::string tmp("test2");
	std::cout << tmp << "\n";
	qwe.WriteStringToFile(tmp);
	tmp = "234";
	std::cout << tmp << "\n";
	tmp = qwe.ReadStringFromFile();
	std::cout << tmp << "\n";
	tmp = qwe.ReadStringFromFile();
	std::cout << tmp << "\n";
	tmp = qwe.ReadStringFromFile();
	std::cout << tmp << "\n";
	*/
	
	//std::cout << sizeof password;

	/*
	std::string tmp = getpass("Enter password: ");

	std::cout << std::endl << tmp;*/
	//end testing

	int errorCode = 0;

	try
	{
		//AuthClass localAuth;
		//errorCode = localAuth.run();
		AJIOBMenuClass localMenu;
		localMenu.AdminMenu();
		//errorCode = localMenu.run(localAuth.run());
	}
	catch (...)
	{
		errorCode = -1;
	}

	return errorCode;
}
