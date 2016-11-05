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

	bool SetID(const ul& newID);
	//ul GetID() const;
	Type GetType() const;

	template <typename T>
	friend std::ostream& operator<<(std::ostream& oStr, const DefaultID<T>& ID);

	template <typename T>
	friend std::istream& operator>>(std::istream& s, DefaultID<T>& ID);

	bool EqualByID(const DefaultID<Type>& that) const;
	bool EqualByAll(const DefaultID<Type>& that) const;
	bool operator==(const DefaultID<Type>& that) const;
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
	t = AJIOBTypes::PrivelegeType::none;
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
bool DefaultID<Type>::SetID(const ul& newID)
{
	id = newID;
	return true;
}

template <typename Type>
bool DefaultID<Type>::EqualByID(const DefaultID<Type>& that) const
{
	return (id == that.id);
}

template <typename Type>
bool DefaultID<Type>::EqualByAll(const DefaultID<Type>& that) const
{
	return (EqualByID(that) && (t == that.t));
}

template <typename Type>
bool DefaultID<Type>::operator==(const DefaultID<Type>& that) const
{
	return EqualByID(that);
}

/*
template <typename Type>
ul DefaultID<Type>::GetID() const
{
	return id;
}*/

template <typename Type>
Type DefaultID<Type>::GetType() const
{
	return t;
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

	OutputConsole("Введите уникальный числовой идентификатор пользователя: ");
	ID.id = Input<ul>();
	OutputConsole("Введите права доступа пользователя: ");
	ID.t = static_cast<AJIOBTypes::PrivelegeType> (InputEnum(AJIOBTypes::PrivelegeFieldsAsVector));

	return s;
}