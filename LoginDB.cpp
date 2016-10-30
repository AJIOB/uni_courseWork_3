#include "LoginDB.h"

LoginDB::LoginDB()
	: CryptedDB<OneElementOf::Auth>(LoginDBDefaultWay)
{
	//
}

LoginDB::~LoginDB()
{
	//
}
