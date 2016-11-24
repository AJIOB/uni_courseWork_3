#pragma once

#include <string>

#include "../../binary input&output/templates/BStringIO.h"
#include "../../../view/headers/view.h"
#include "../../enums/PrivelegeType.h"
#include "typedefs.h"

class DefaultID
{
	AJIOBTypes::PrivelegeType::PrivelegeType cl_type;
	uli cl_id;

	void BWrite(const bString& bInfo, strPos& it);
public:
	DefaultID();
	DefaultID(const DefaultID& that);
	DefaultID(const bString& bInfo, strPos& it);
	~DefaultID();

	DefaultID& operator=(const DefaultID& that);

	std::string BRead() const;

	bool SetID(const uli& newID);
	void InputNewType();
	uli GetID() const;
	AJIOBTypes::PrivelegeType::PrivelegeType GetType() const;

	friend std::ostream& operator<<(std::ostream& oStr, const DefaultID& ID);
	friend std::istream& operator>>(std::istream& s, DefaultID& ID);

	bool EqualByID(const DefaultID& that) const;
	bool EqualByAll(const DefaultID& that) const;
	bool operator==(const DefaultID& that) const;
};
