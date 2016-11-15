#pragma once
#include <string>

#include "../../other/templates/MyContainer.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "Publisher.h"
#include "../../other/headers/ISBNClass.h"

#ifndef AJIOB_UI
#define AJIOB_UI
typedef unsigned long int uli;
#endif

namespace OneElementOf
{
	class Country;
}

class CountryDBClass;

class OneElementOf::Country
{
	friend CountryDBClass;

	std::string cl_nameOfCountry;
	ISBNOnePart cl_countryISBNPart;
	MyContainer<OneElementOf::Publisher> cl_publishers;

	CountryDBClass* cl_parentDB;

	void BWrite(const std::string& bInfo, strPos& it);

	bool AddByISBN(const ISBNClass& num);

	OneElementOf::Country& GetParentElement(const int index) const;
public:
	Country(void* parentDB = nullptr);
	Country(const Country& that);
	Country(const std::string& bInfo, strPos& it, void* parentDB);
	~Country();

	Country& operator=(const Country& that);

	std::string GetName() const;
	ISBNOnePart GetISBNPart() const;
	MyContainer<OneElementOf::Publisher> GetPublishers() const;

	std::string BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Country& that);
	friend std::istream& operator>> (std::istream& s, Country& that);

	bool InputNewName();
	bool InputNewISBNPart();
	bool WorkWithPublishers();

	int FindByName(const std::string& name);

	bool EqualByISBNPart(const Country& that) const;

	bool operator==(const Country& that) const;
};