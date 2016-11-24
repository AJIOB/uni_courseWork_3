#pragma once

#include "../../enums/ISBNType.h"
#include "ISBNOnePart.h"
#include "../../binary input&output/templates/BStringIO.h"
#include "../../exceptions/AllExceptions.h"
#include "StringFuncs.h"

const auto numOfISBNFields = 4;

#ifndef AJIOB_ULLI
#define AJIOB_ULLI
typedef unsigned long long int ulli;
#endif


class ISBNClass
{
	AJIOBTypes::ISBNType::ISBNType cl_type;
	ISBNOnePart cl_fields[numOfISBNFields];

	uli CalculateISBN10CheckDigit() const;
	uli CalculateISBN13CheckDigit() const;

	ulli GetAsNumWithoutCheckDigit() const;

	bool ParseConsoleString(const std::string&);

	void BWrite(const bString& bInfo, strPos& it);

public:
	ISBNClass();
	ISBNClass(const bString& bInfo, strPos& it);
	~ISBNClass();

	std::string BRead() const;

	std::string GetAsString() const;

	friend std::ostream& operator<<(std::ostream& s, const ISBNClass& that);
	friend std::istream& operator>>(std::istream& s, ISBNClass& that);

	bool operator==(const ISBNClass& that) const;
	bool operator!=(const ISBNClass& that) const;
	bool operator>(const ISBNClass& that) const;
	bool operator<(const ISBNClass& that) const;

	ISBNOnePart& operator[](const int index);
	const ISBNOnePart& operator[](const int index) const;
};
