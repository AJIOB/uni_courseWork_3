#pragma once

#include <vector>

#include "CryptedDB.h"
#include "Auth.h"
#include "WorkWithStreams.h"
#include "ExternalLib.h"

const std::string wayToLoginDB = "auth.db";

class AuthClass
{
	CryptedDB<OneElementOf::Auth> loginDB;

	OneElementOf::Auth CurrentUser;

	void AuthProcessing();

public:
	//����������� (�������� �� ��)
	AuthClass();
	//����������
	~AuthClass();

	//�������� �������. ���������� ID ��������������� ������������
	DefaultID<AJIOBTypes::PrivelegeType> run();
};
