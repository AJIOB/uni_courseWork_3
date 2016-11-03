#pragma once

#include <vector>

#include "../../view/headers/view.h"
//#include "../../view/headers/WorkWithStreams.h"
//#include "../../external/headers/ExternalLib.h"
#include "../../model/dbs/templates/CryptedDB.h"
#include "../../model/one element of db/headers/Auth.h"

const std::string wayToLoginDB = "auth.db";

class AuthClass
{
	CryptedDB<OneElementOf::Auth> loginDB;

	OneElementOf::Auth CurrentUser;

	void AuthProcessing();

public:
	//конструктор (загрузка из БД)
	AuthClass();
	//деструктор
	~AuthClass();

	//основная функция. Возвращает ID авторизованного пользователя
	DefaultID<AJIOBTypes::PrivelegeType> run();
};
