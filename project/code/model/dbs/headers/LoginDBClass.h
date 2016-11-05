#pragma once
#include "../templates/CryptedDB.h"
#include "../../one element of db/headers/Auth.h"

const char LoginDBDefaultWay[] = "project\\dbs\\auth.db";

class LoginDBClass : private CryptedDB<OneElementOf::Auth>
{
	void Load(bool isReadOnly = true);

	void UpdateElementWithIndex(int goodIndexOnly) override;

public:
	LoginDBClass(bool isReadOnly = false);
	~LoginDBClass();
	
	void Unload();

	void Add();
	void Show() const;
	int Find(const OneElementOf::Auth& currLP) const;
	void Update();
	void Delete();

	OneElementOf::Auth& Get(int index);
	const OneElementOf::Auth& Get(int index) const;
	OneElementOf::Auth& operator[](int index);
};
