#pragma once
#include <string>
//#include <vector>

//#include "../../../view/headers/StreamInput.h"
#include "../../other/templates/MyContainer.h"
#include "../../other/headers/ISBNOnePart.h"
#include "../../binary input&output/templates/BStringIO.h"
//#include "Country.h"

#ifndef AJIOB_BStringIO_header
#define AJIOB_BStringIO_header

#include "../../other/headers/typedefs.h"

namespace BStringIO
{
	template <typename InfoType>
	InfoType ReadBInfo(const bString& str, strPos& iterator);

	template <typename InfoType>
	bString MakeBString(const InfoType& info);
}

#endif

//class PublisherDBClass;

namespace OneElementOf
{
	class Publisher;
	class Country;
}

class OneElementOf::Publisher
{
	friend Country;

	std::string cl_name;
	std::string cl_city;
	MyContainer<ISBNOnePart> cl_ISBN_PublisherPart;
	//int cl_ISBN_PublisherPart;

	Country* cl_parent;

	void BWrite(const bString& bInfo, strPos& it);

public:
	Publisher(void* parent = nullptr);
	Publisher(const Publisher& that);
	Publisher(const bString& bInfo, strPos& it, void* parent);
	~Publisher();

	bool AddISBNPart(const ISBNOnePart& newISBN);

	Publisher& operator=(const Publisher& that);

	std::string GetName() const;
	std::string GetCity() const;
	MyContainer<ISBNOnePart> GetISBNParts() const;


	bString BRead() const;
	
	//friend Publisher BStringIO::ReadBInfo<Publisher>(const std::string& str, strPos& iterator);
	//friend std::string BStringIO::MakeBString(const Publisher& info);

	friend std::ostream& operator<< (std::ostream& s, const Publisher& that);
	friend std::istream& operator>> (std::istream& s, Publisher& that);

	bool WorkWithISBNPublisherPart();

	bool InputNewName();
	bool InputNewCity();
	bool WorkWithISBNPart();

	bool EqualByName(const Publisher& that) const;
	bool EqualByNameAndCity(const Publisher& that) const;
	bool EqualByISBNPart(const ISBNOnePart& ISBNpart) const;

	bool operator==(const Publisher& that) const;
	bool operator>(const Publisher& that) const;
	bool operator<(const Publisher& that) const;

	bool UpdateMe();
};


template <>
inline OneElementOf::Publisher BStringIO::ReadBInfo<OneElementOf::Publisher>(const bString& str, strPos& iterator)
{
	return OneElementOf::Publisher(str, iterator, nullptr);
}

template <>
inline bString BStringIO::MakeBString<OneElementOf::Publisher>(const OneElementOf::Publisher& info)
{
	return info.BRead();
}