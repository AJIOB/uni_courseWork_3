#pragma once

#include <vector>

#include "BFileIO.h"

template <typename oneElementOfDB>
class DefaultDB : public AJIOB_BinaryFileInputOutput
{
	//поля
	std::vector<oneElementOfDB> cl_ourArray;

	//методы
	void ReadAll();
public:
	DefaultDB(const std::string& wayToFile);
	~DefaultDB();
};


//cpp

template <typename oneElementOfDB>
void DefaultDB<oneElementOfDB>::ReadAll()
{
	//std::string a;
	while (!fin.eof())
	{
		std::string str = ReadStringFromFile();
		oneElementOfDB currentElem(str);
	}
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::DefaultDB(const std::string& wayToFile):AJIOB_BinaryFileInputOutput(wayToFile)
{
}

template <typename oneElementOfDB>
DefaultDB<oneElementOfDB>::~DefaultDB()
{
}
