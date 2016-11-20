#pragma once
#include "../templates/CryptedDB.h"
#include "../../one element of db/headers/Auth.h"
#include "../../../view/headers/view.h"

const char LoginDBDefaultWay[] = "project\\dbs\\auth.db";

class AuthDBClass : public CryptedDB<OneElementOf::Auth>
{
	void Load(bool isReadOnly = true);

	bool UpdateElement(OneElementOf::Auth& elem) override;

public:
	AuthDBClass(bool isReadOnly = false);
	~AuthDBClass();
	/*
	void Save();
	void Unload();
	/*
	void Add();
	void Show() const;*/
	int Find(const OneElementOf::Auth& currLP) const;
	/*void Update();
	void Delete();
	/*/
	OneElementOf::Auth& GetElement(int index);
	const OneElementOf::Auth& GetElement(int index) const;
	OneElementOf::Auth& operator[](int index);

	//void SomethingIsChanged() override;
};
