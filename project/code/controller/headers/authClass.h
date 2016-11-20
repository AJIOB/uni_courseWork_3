#pragma once

#include <vector>

#include "../../view/headers/view.h"
#include "../../model/dbs/headers/AuthDBClass.h"
#include "../../model/exceptions/AllExceptions.h"

class AuthClass
{
	AuthDBClass* cl_loginDB;
	bool cl_isGetDBbyExternal;

	OneElementOf::Auth cl_currentUser;

public:
	//конструктор (загрузка из БД)
	AuthClass();

	AuthClass(AuthDBClass* loginDB);
	//деструктор
	~AuthClass();

	//основная функция. Возвращает ID авторизованного пользователя
	OneElementOf::Auth run();
};
