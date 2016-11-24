#pragma once
#include <string>
#include <vector>

#include "../../other/templates/MyContainer.h"
#include "../../other/headers/ISBNClass.h"
#include "../../other/headers/IsPublicationGetted.h"
#include "../../dbs/headers/PublicationDBClass.h"
#include "../../other/headers/typedefs.h"

//#include "Country.h"


class CopiesDBClass;

namespace OneElementOf
{
	class Copies;
}

class OneElementOf::Copies
{
	
	ISBNClass cl_ISBN;
	MyContainer<IsPublicationGetted> cl_isThisCopyGetted;

	CopiesDBClass* cl_parent;

	void BWrite(const bString& bInfo, strPos& it);

	int CopiesThatNotArchieved() const;
	int CopiesYouCanGetNow() const;

	PublicationDBClass* GetConnectedPublicationDB() const;
public:
	Copies(void* parent = nullptr);
	Copies(const Copies& that);
	Copies(const bString& bInfo, strPos& it, void* parent);
	~Copies();

	Copies& operator=(const Copies& that);

	ISBNClass GetISBN() const;
	MyContainer<IsPublicationGetted> GetArrayOfInfoAboutCopies() const;

	bString BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Copies& that);
	friend std::istream& operator>> (std::istream& s, Copies& that);

	bool EqualByISBN(const Copies& that) const;

	bool operator==(const Copies& that) const;
	bool operator<(const Copies& that) const;
	bool operator>(const Copies& that) const;
	
	//Update
	bool InputNewISBN();
	bool WorkWithCopies();

	bool UpdateMe();
};


template <>
inline OneElementOf::Copies BStringIO::ReadBInfo<OneElementOf::Copies>(const bString& str, strPos& iterator)
{
	return OneElementOf::Copies(str, iterator, nullptr);
}

template <>
inline bString BStringIO::MakeBString<OneElementOf::Copies>(const OneElementOf::Copies& info)
{
	return info.BRead();
}