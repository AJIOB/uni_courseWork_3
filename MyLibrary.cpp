#include "MyLibrary.h"

void defaultFunction()
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

	//end testing

	AuthClass localAuth;

	localAuth.run();
}
