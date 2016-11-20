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
	//����������� (�������� �� ��)
	AuthClass();

	AuthClass(AuthDBClass* loginDB);
	//����������
	~AuthClass();

	//�������� �������. ���������� ID ��������������� ������������
	OneElementOf::Auth run();
};
