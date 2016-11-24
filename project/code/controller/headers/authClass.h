#pragma once

#include <vector>

#include "../../view/headers/view.h"
//#include "../../model/dbs/headers/AuthDBClass.h"
#include "../../model/exceptions/AllExceptions.h"
#include "../../model/dbs/headers/UserDBClass.h"

class AuthClass
{
	UserDBClass* cl_dbWithAuthInfo;
	bool cl_isGetDBbyExternal;

	//OneElementOf::Auth cl_currentUser;

public:
	//����������� (�������� �� ��)
	AuthClass();

	AuthClass(UserDBClass* loginDB);
	//����������
	~AuthClass();

	//�������� �������. ���������� ID ��������������� ������������
	DefaultID run();
};
