#pragma once

#include "../templates/DefaultDB.h"
#include "../../one element of db/headers/Publication.h"
#include "CountryDBClass.h"
//#include "CopiesDBClass.h"

const char PublicationDBDefaultWay[] = "project\\dbs\\publications.db";

class PublicationDBClass : public DefaultDB<OneElementOf::Publication>
{
	friend OneElementOf::Publication;

	CountryDBClass* cl_connected_CountryDB;
	//CopiesDBClass* cl_connected_CopiesDB;

	void Load(bool isReadOnly = true);

	//bool UpdateElement(OneElementOf::Publication& elem) override;

public:
	PublicationDBClass(CountryDBClass* dbToConnect/*, CopiesDBClass* copiesDBToConnect*/, bool isReadOnly = false);
	~PublicationDBClass();
	/*
	void Save();
	void Unload();

	int Add();
	void Show() const override;
	void Update() override;
	void Delete() override;
	/*//*
	OneElementOf::Publication& GetElement(int index);
	const OneElementOf::Publication& GetElement(int index) const;
	OneElementOf::Publication& operator[](int index);

	void SomethingIsChanged() override;
	/*/
	int FindByISBN(const ISBNClass& ISBNToFind) const;
};