#pragma once

#include <string>
#include "../../binary input&output/templates/BStringIO.h"
#include "../../../view/headers/view.h"
#include "../../enums/PrivelegeType.h"

typedef unsigned long int ul;

template <typename Type>
class DefaultID
{
	Type t;
	ul id;

	void BWrite(const std::string& bInfo, strPos& it);
public:
	DefaultID();
	DefaultID(const std::string& bInfo, strPos& it);
	~DefaultID();

	std::string BRead();

	template <typename T>
	friend std::ostream& operator<<(std::ostream& oStr, const DefaultID<T>& ID);

	template <typename T>
	friend std::istream& operator>>(std::istream& s, DefaultID<T>& ID);
};


template <typename Type>
void DefaultID<Type>::BWrite(const std::string& bInfo, strPos& it)
{
	t = BStringIO::ReadBInfo<Type>(bInfo, it);
	id = BStringIO::ReadBInfo<ul>(bInfo, it);
}

template <typename Type>
DefaultID<Type>::DefaultID()
{
	id = 0;
}

template <typename Type>
DefaultID<Type>::DefaultID(const std::string& bInfo, strPos& it)
{
	BWrite(bInfo, it);
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

template <typename Type>
std::ostream& operator<<(std::ostream& oStr, const DefaultID<Type>& ID)
{
	oStr << "Логин: " << ID.id << std::endl;
	oStr << "Права доступа: " << OutputEnum(AJIOBTypes::PrivelegeFieldsAsVector, static_cast<int>(ID.t)) << std::endl;
	return oStr;
}

template <typename Type>
std::istream& operator>>(std::istream& s, DefaultID<Type>& ID)
{
	//s << "Логин: " << ID.id << std::endl;
	//s << "Права доступа: " << ID.t << std::endl;

	OutputInfo("Введите уникальный числовой идентификатор пользователя: ");
	ID.id = Input<ul>();
	OutputInfo("Введите права доступа пользователя: ");
	ID.t = static_cast<AJIOBTypes::PrivelegeType> (InputEnum(AJIOBTypes::PrivelegeFieldsAsVector));

	return s;
}