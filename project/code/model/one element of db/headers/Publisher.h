#pragma once
#include <string>
#include <vector>

#include "../../../view/headers/StreamInput.h"
#include "../../other/templates/MyContainer.h"
#include "../../other/headers/ISBNOnePart.h"
//#include "Country.h"
/*
#ifndef AJIOB_UI
#define AJIOB_UI

typedef unsigned long int uli;

#endif*/

#ifndef AJIOB_BStringIO_header
#define AJIOB_BStringIO_header

#ifndef AJIOB_STRPOS
#define AJIOB_STRPOS
typedef unsigned int strPos;
#endif

namespace BStringIO
{
	template <typename InfoType>
	InfoType ReadBInfo(const std::string& str, strPos& iterator);

	template <typename InfoType>
	std::string GetBString(const InfoType& info);
}

#endif

//class PublisherBDClass;

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

	Country* cl_parent;

	void BWrite(const std::string& bInfo, strPos& it);

public:
	Publisher(void* parent = nullptr);
	Publisher(const Publisher& that);
	Publisher(const std::string& bInfo, strPos& it, void* parent);
	~Publisher();

	bool AddISBNPart(const ISBNOnePart& newISBN);

	Publisher& operator=(const Publisher& that);

	std::string GetName() const;
	std::string GetCity() const;
	MyContainer<ISBNOnePart> GetISBNParts() const;


	std::string BRead() const;
	
	friend Publisher BStringIO::ReadBInfo<Publisher>(const std::string& str, strPos& iterator);
	friend std::string GetBString(const Publisher& info);

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

	bool UpdateMe();
};
