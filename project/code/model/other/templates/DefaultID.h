#pragma once

#include <string>
#include "../../binary input&output/templates/BStringIO.h"
#include "../../../view/headers/view.h"
#include "../../enums/PrivelegeType.h"

#ifndef AJIOB_UI
#define AJIOB_UI

typedef unsigned long int uli;

#endif

template <typename Type>
class DefaultID
{
	Type cl_type;
	uli cl_id;

	void BWrite(const std::string& bInfo, strPos& it);
public:
	DefaultID();
	DefaultID(const DefaultID& that);
	DefaultID(const std::string& bInfo, strPos& it);
	~DefaultID();

	DefaultID<Type>& operator=(const DefaultID<Type>& that);

	std::string BRead();

	bool SetID(const uli& newID);
	void InputNewType();
	uli GetID() const;
	Type GetType() const;

	template <typename T>
	friend std::ostream& operator<<(std::ostream& oStr, const DefaultID<T>& ID);

	template <typename T>
	friend std::istream& operator>>(std::istream& s, DefaultID<T>& ID);

	bool EqualByID(const DefaultID<Type>& that) const;
	bool EqualByAll(const DefaultID<Type>& that) const;
	bool operator==(const DefaultID<Type>& that) const;
};







//cpp

template <typename Type>
void DefaultID<Type>::BWrite(const std::string& bInfo, strPos& it)
{
	cl_type = BStringIO::ReadBInfo<Type>(bInfo, it);
	cl_id = BStringIO::ReadBInfo<uli>(bInfo, it);
}

template <typename Type>
DefaultID<Type>::DefaultID()
{
	cl_id = 0;
	cl_type = AJIOBTypes::PrivelegeType::none;
}

template <typename Type>
DefaultID<Type>::DefaultID(const DefaultID& that)
{
	(*this) = that;
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
DefaultID<Type>& DefaultID<Type>::operator=(const DefaultID<Type>& that)
{
	cl_id = that.cl_id;
	cl_type = that.cl_type;
	return (*this);
}

template <typename Type>
std::string DefaultID<Type>::BRead()
{

	return (BStringIO::GetBString(cl_type) + BStringIO::GetBString(cl_id));
}

template <typename Type>
bool DefaultID<Type>::SetID(const uli& newID)
{
	cl_id = newID;
	return true;
}

template <typename Type>
void DefaultID<Type>::InputNewType()
{
	Stream::Input(cl_type);
}

template <typename Type>
bool DefaultID<Type>::EqualByID(const DefaultID<Type>& that) const
{
	return (cl_id == that.cl_id);
}

template <typename Type>
bool DefaultID<Type>::EqualByAll(const DefaultID<Type>& that) const
{
	return (EqualByID(that) && (cl_type == that.cl_type));
}

template <typename Type>
bool DefaultID<Type>::operator==(const DefaultID<Type>& that) const
{
	return EqualByID(that);
}


template <typename Type>
uli DefaultID<Type>::GetID() const
{
	return cl_id;
}

template <typename Type>
Type DefaultID<Type>::GetType() const
{
	return cl_type;
}

template <typename Type>
std::ostream& operator<<(std::ostream& oStr, const DefaultID<Type>& ID)
{
	oStr << "Логин: " << ID.cl_id << std::endl;
	oStr << "Права доступа: " << OutputEnum(AJIOBTypes::PrivelegeFieldsAsVector, static_cast<int>(ID.cl_type)) << std::endl;
	return oStr;
}

template <typename Type>
std::istream& operator>>(std::istream& s, DefaultID<Type>& ID)
{
	OutputConsole("Введите уникальный числовой идентификатор пользователя: ");
	ID.cl_id = Stream::Input<uli>();
	OutputConsole("Введите права доступа пользователя: ");
	ID.cl_type = static_cast<AJIOBTypes::PrivelegeType::PrivelegeType> (Stream::InputEnum(AJIOBTypes::PrivelegeFieldsAsVector));

	return s;
}