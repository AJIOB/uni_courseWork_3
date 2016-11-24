#pragma once

//#include <algorithm>

#include "../templates/DefaultDB.h"
#include "../../one element of db/headers/Country.h"
#include "../../other/headers/ISBNClass.h"

const char CountryDBDefaultWay[] = "project\\dbs\\countries.db";

class CountryDBClass : public DefaultDB<OneElementOf::Country>
{
	friend OneElementOf::Country;
	void Load(bool isReadOnly = true);

public:
	CountryDBClass(bool isReadOnly = false);
	~CountryDBClass();
	
	/*
	void Add();
	void Show() const override;*/
	bool AddByISBN(const ISBNClass& currentISBN);/*
	void Update() override;
	void Delete() override;
	/*//*
	OneElementOf::Country& GetElement(int index);
	const OneElementOf::Country& GetElement(int index) const;
	OneElementOf::Country& operator[](int index);
	/*/
	int FindByName(const std::string& strToFind);
	int FindByISBNPart(const ISBNOnePart& partToFind);

	std::string GetInfo(const ISBNClass& num);

	//void SomethingIsChanged() override;
};