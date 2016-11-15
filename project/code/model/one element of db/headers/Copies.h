#pragma once
#include <string>
#include <vector>

#include "../../../view/headers/StreamInput.h"
#include "../../other/templates/MyContainer.h"
#include "../../other/headers/ISBNClass.h"
//#include "Country.h"
/*
#ifndef AJIOB_UI
#define AJIOB_UI

typedef unsigned long int uli;

#endif*/


#ifndef AJIOB_STRPOS
#define AJIOB_STRPOS
typedef unsigned int strPos;
#endif

//class PublisherBDClass;

namespace OneElementOf
{
	class Copies;
}

class OneElementOf::Copies
{
	
	ISBNClass cl_ISBN;
	/*std::string cl_name;
	std::string cl_authors;
	uli cl_yearOfCopies;
	/*/
	//CopiesDBClass* cl_parent;

	void BWrite(const std::string& bInfo, strPos& it);

public:
	Copies(void* parent = nullptr);
	Copies(const Copies& that);
	Copies(const std::string& bInfo, strPos& it, void* parent);
	~Copies();

	Copies& operator=(const Copies& that);

	ISBNClass GetISBN() const;
	std::string GetName() const;
	std::string GetAuthor() const;
	uli GetYearOfPublicatiion() const;

	std::string BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Copies& that);
	friend std::istream& operator>> (std::istream& s, Copies& that);

	bool EqualByISBN(const Copies& that) const;

	bool operator==(const Copies& that) const;

	//Update
	bool InputNewISBN();
	bool InputNewName();
	bool InputNewAuthor();
	bool InputNewYear();

};
