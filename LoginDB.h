#pragma once
#include "CryptedDB.h"
#include "Auth.h"

const char LoginDBDefaultWay[] = "auth.db";

class LoginDB : private CryptedDB<OneElementOf::Auth>
{

public:
	LoginDB();
	~LoginDB();
};
