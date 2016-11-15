#pragma once
#include <string>


#include "../../binary input&output/templates/BStringIO.h"
#include "../../other/headers/ISBNClass.h"
#include "../../dbs/headers/CountryDBClass.h"

namespace OneElementOf
{
	class Publication;
}

class PublicationDBClass;

class OneElementOf::Publication
{
	ISBNClass cl_ISBN;
	std::string cl_name;
	std::string cl_authors;
	uli cl_yearOfPublication;

	PublicationDBClass* cl_parent;

	void BWrite(const std::string& bInfo, strPos& it);

	CountryDBClass* GetConnectedCountryDB() const;

public:
	Publication(void* parent = nullptr);
	Publication(const Publication& that);
	Publication(const std::string& bInfo, strPos& it, void* parent);
	~Publication();

	Publication& operator=(const Publication& that);

	ISBNClass GetISBN() const;
	std::string GetName() const;
	std::string GetAuthor() const;
	uli GetYearOfPublicatiion() const;

	std::string BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Publication& that);
	friend std::istream& operator>> (std::istream& s, Publication& that);

	bool EqualByISBN(const Publication& that) const;

	bool operator==(const Publication& that) const;

	//Update
	bool InputNewISBN();
	bool InputNewName();
	bool InputNewAuthor();
	bool InputNewYear();

};



/*

	
	/*
	friend Publication BStringIO::ReadBInfo<Publication>(const std::string& str, strPos& iterator);
	friend std::string GetBString(const Publication& info);
	/*
	friend std::ostream& operator<< (std::ostream& s, const Publication& that);
	friend std::istream& operator>> (std::istream& s, Publication& that);
	/*
	bool WorkWithISBNPublicationPart();

	bool InputNewName();
	bool InputNewCity();
	bool WorkWithISBNPart();

	bool UpdateMe();*/