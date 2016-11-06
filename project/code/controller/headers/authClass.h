#pragma once

#include <vector>

#include "../../view/headers/view.h"
//#include "../../view/headers/WorkWithStreams.h"
//#include "../../external/headers/ExternalLib.h"
//#include "../../model/dbs/templates/CryptedDB.h"
//#include "../../model/one element of db/headers/Auth.h"
#include "../../model/dbs/headers/LoginDBClass.h"
#include "../../model/exceptions/AllExceptions.h"

class AuthClass
{
	const LoginDBClass* loginDB;
	bool isGetDBbyExternal;

	OneElementOf::Auth CurrentUser;

public:
	//����������� (�������� �� ��)
	AuthClass();

	AuthClass(const LoginDBClass* loginDB);
	//����������
	~AuthClass();

	//�������� �������. ���������� ID ��������������� ������������
	DefaultID<AJIOBTypes::PrivelegeType> run() const;
};
