#pragma once

#include <iostream>
#include <string>

#include "../../../view/headers/view.h"
#include "typedefs.h"

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
	bool operator<(const ISBNOnePart& that) const;
	bool operator>(const ISBNOnePart& that) const;

	bool UpdateMe();
};

std::ostream& operator<<(std::ostream& s, const ISBNOnePart& elem);
std::istream& operator>>(std::istream& s, ISBNOnePart& elem);