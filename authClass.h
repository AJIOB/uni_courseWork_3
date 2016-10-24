#pragma once

#include <vector>

#include "CryptedDB.h"
#include "Auth.h"

const std::string wayToLoginDB = "auth.db";

class AuthClass
{
	CryptedDB<OneElementOf::Auth> loginDB;
	//std::vector<Auth> DBArray;

	void ReadAllFile();
public:
	//конструктор (загрузка из БД)
	AuthClass();
	//деструктор
	~AuthClass();

	//основная функция
	int run();
};
