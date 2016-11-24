#pragma once
#include <string>

#include "../../binary input&output/templates/BStringIO.h"
#include "../../other/headers/ISBNClass.h"
#include "../../dbs/headers/CountryDBClass.h"
//#include "../../dbs/headers/CopiesDBClass.h"

namespace OneElementOf
{
	class Publication;
}

class PublicationDBClass;
class CopiesDBClass;

class OneElementOf::Publication
{
	ISBNClass cl_ISBN;
	std::string cl_name;
	std::string cl_authors;
	uli cl_yearOfPublication;
	MyContainer<std::string> cl_userTags;

	PublicationDBClass* cl_parent;

	void BWrite(const bString& bInfo, strPos& it);

	CountryDBClass* GetConnectedCountryDB() const;
	//CopiesDBClass* GetConnectedCopiesDB() const;

public:
	Publication(void* parent = nullptr);
	Publication(const Publication& that);
	Publication(const bString& bInfo, strPos& it, void* parent);
	~Publication();

	Publication& operator=(const Publication& that);

	ISBNClass GetISBN() const;
	std::string GetName() const;
	std::string GetAuthor() const;
	uli GetYearOfPublication() const;
	MyContainer<std::string> GetUserTags() const;

	bString BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Publication& that);
	friend std::istream& operator>> (std::istream& s, Publication& that);

	bool EqualByISBN(const Publication& that) const;

	bool operator==(const Publication& that) const;
	bool operator<(const Publication& that) const;
	bool operator>(const Publication& that) const;

	//Update
	bool InputNewISBN();
	bool InputNewName();
	bool InputNewAuthor();
	bool InputNewYear();
	bool WorkWithTags();

	//void InputElem(bool ISBNIsGettedByParametr, const ISBNClass ISBN = ISBNClass());

	bool UpdateMe();
};

template <>
inline OneElementOf::Publication BStringIO::ReadBInfo<OneElementOf::Publication>(const bString& str, strPos& iterator)
{
	return OneElementOf::Publication(str, iterator, nullptr);
}

template <>
inline bString BStringIO::MakeBString<OneElementOf::Publication>(const OneElementOf::Publication& info)
{
	return info.BRead();
}