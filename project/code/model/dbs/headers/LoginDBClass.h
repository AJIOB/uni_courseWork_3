#pragma once
#include "../templates/CryptedDB.h"
#include "../../one element of db/headers/Auth.h"

const char LoginDBDefaultWay[] = "project\\dbs\\auth.db";

class LoginDBClass : private CryptedDB<OneElementOf::Auth>
{
	void Load(bool isReadOnly = true);

public:
	LoginDBClass(bool isReadOnly = true);
	~LoginDBClass();
	
	void Unload();

	void Add();
	void Show() const;
	//void Delete();
};
