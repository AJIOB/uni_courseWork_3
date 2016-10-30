#pragma once

#include <string>
#include "BStringIO.h"

typedef unsigned long int ul;

template <typename Type>
class DefaultID
{
	Type t;
	ul id;

	void BWrite(const std::string& bInfo);
public:
	DefaultID();
	explicit DefaultID(const std::string& bInfo);
	~DefaultID();

	std::string BRead();

	friend std::ostream& operator>>(std::ostream& oStr, const DefaultID<Type>& ID);
};


template <typename Type>
void DefaultID<Type>::BWrite(const std::string& bInfo)
{
	//BStringIO::GetBString(t) + BStringIO::GetBString(id)

	strPos it = 0;
	t = BStringIO::ReadBInfo<Type>(bInfo, it);
	id = BStringIO::ReadBInfo<ul>(bInfo, it);
}

template <typename Type>
DefaultID<Type>::DefaultID()
{
	id = 0;
}

template <typename Type>
DefaultID<Type>::DefaultID(const std::string& bInfo)
{
	BWrite(bInfo);
}

template <typename Type>
DefaultID<Type>::~DefaultID()
{
}

template <typename Type>
std::string DefaultID<Type>::BRead()
{

	return (BStringIO::GetBString(t) + BStringIO::GetBString(id));
}
