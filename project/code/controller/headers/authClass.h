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
	LoginDBClass* cl_loginDB;
	bool cl_isGetDBbyExternal;

	OneElementOf::Auth cl_currentUser;

public:
	//����������� (�������� �� ��)
	AuthClass();

	AuthClass(LoginDBClass* loginDB);
	//����������
	~AuthClass();

	//�������� �������. ���������� ID ��������������� ������������
	OneElementOf::Auth run();
};
