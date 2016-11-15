#pragma once

#include <iostream>
#include <string>

#include "../../../view/headers/view.h"

#ifndef AJIOB_UI
#define AJIOB_UI

typedef unsigned long int uli;

#endif

#ifndef AJIOB_USI
#define AJIOB_USI

typedef unsigned short int usi;

#endif

struct ISBNOnePart
{
	uli ISBNpart;
	usi numOfElements;

	//friend std::ostream& operator<<(std::ostream& s, const ISBNOnePart& elem);
	//friend std::istream& operator>>(std::istream& s, ISBNOnePart& elem);

	ISBNOnePart();

	std::string GetString() const;
	bool SetString(const std::string& num);

	bool operator==(const ISBNOnePart& that) const;
	bool operator!=(const ISBNOnePart& that) const;

	bool UpdateMe();
};

std::ostream& operator<<(std::ostream& s, const ISBNOnePart& elem);
std::istream& operator>>(std::istream& s, ISBNOnePart& elem);