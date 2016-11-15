#pragma once

#include "../templates/DefaultDB.h"
#include "../../one element of db/headers/Publication.h"
#include "CountryDBClass.h"

const char PublicationDBDefaultWay[] = "project\\dbs\\publications.db";

class PublicationDBClass : private DefaultDB<OneElementOf::Publication>
{
	friend OneElementOf::Publication;

	CountryDBClass* cl_connected_CountryDB;

	void Load(bool isReadOnly = true);

	bool UpdateElement(OneElementOf::Publication& elem) override;

public:
	PublicationDBClass(CountryDBClass* dbToConnect, bool isReadOnly = false);
	~PublicationDBClass();
	
	void Save();
	void Unload();

	void Add();
	void Show() const override;
	void Update() override;
	void Delete() override;

	OneElementOf::Publication& GetElement(int index);
	const OneElementOf::Publication& GetElement(int index) const;
	OneElementOf::Publication& operator[](int index);

	void SomethingIsChanged() override;

	int FindByISBNPart(const ISBNClass& ISBNToFind);
};