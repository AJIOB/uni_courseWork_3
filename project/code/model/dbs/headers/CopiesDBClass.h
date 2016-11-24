#pragma once

#include "../templates/DefaultDB.h"
#include "../../one element of db/headers/Copies.h"
#include "PublicationDBClass.h"

const char CopiesDBDefaultWay[] = "project\\dbs\\copies.db";

class CopiesDBClass : public DefaultDB<OneElementOf::Copies>
{
	friend OneElementOf::Copies;

	PublicationDBClass* cl_connected_PublicationDB;

	void Load(bool isReadOnly = true);

public:
	CopiesDBClass(PublicationDBClass* dbToConnect, bool isReadOnly = false);
	~CopiesDBClass();
	/*
	void Save();
	void Unload();
	/*
	int Add();
	void Show() const override;
	void Update() override;
	void Delete() override;
	/*//*
	OneElementOf::Copies& GetElement(int index);
	const OneElementOf::Copies& GetElement(int index) const;
	OneElementOf::Copies& operator[](int index);
	/*/
	//void SomethingIsChanged() override;

	int FindByISBN(const ISBNClass& ISBNToFind) const;
};