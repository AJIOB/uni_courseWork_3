#pragma once

#include "../templates/DefaultDB.h"
#include "../../one element of db/headers/Country.h"

const char CountryDBDefaultWay[] = "project\\dbs\\countries.db";

class CountryDBClass : private DefaultDB<OneElementOf::Country>
{
	void Load(bool isReadOnly = true);

	bool UpdateElement(OneElementOf::Country& elem) override;

public:
	CountryDBClass(bool isReadOnly = false);
	~CountryDBClass();
	
	void Save();
	void Unload();

	void Add() override;
	void Show() const override;
	int FindByISBNPart(const uli& currentISBNCountryPart) const;
	void Update() override;
	void Delete() override;

	OneElementOf::Country& GetElement(int index);
	const OneElementOf::Country& GetElement(int index) const;
	OneElementOf::Country& operator[](int index);

	void SomethingIsChanged();
};