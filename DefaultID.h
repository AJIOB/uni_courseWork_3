#pragma once

typedef unsigned long int ul;

template <typename Type>
class DefaultID
{
	Type t;
	ul id; 
public:
	DefaultID();
	~DefaultID();

};


template <typename Type>
DefaultID<Type>::DefaultID()
{
}

template <typename Type>
DefaultID<Type>::~DefaultID()
{
}

