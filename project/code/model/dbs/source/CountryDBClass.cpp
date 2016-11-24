#include "../headers/CountryDBClass.h"
#include "../../one element of db/headers/Publisher.h"

CountryDBClass::CountryDBClass(bool isReadOnly)
	: DefaultDB<OneElementOf::Country>(CountryDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
}

CountryDBClass::~CountryDBClass()
{
	Unload();
}

void CountryDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

/*
void CountryDBClass::Add()
{
	DefaultDB<OneElementOf::Country>::Add(true);
}

void CountryDBClass::Show() const
{
	DefaultDB<OneElementOf::Country>::Show();
}
*/
bool CountryDBClass::AddByISBN(const ISBNClass& currentISBN)
{
	OneElementOf::Country tmpCountry(this);

	tmpCountry.cl_countryISBNPart = currentISBN[1];

	int indexOfOurCountry = -1;

	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].EqualByISBNPart(tmpCountry))
		{
			indexOfOurCountry = i;
			break;
		}
	}

	bool result = false;

	if (indexOfOurCountry < 0)
	{
		OutputConsole("Введите название региона (страны) издательства:");
		Stream::Input(tmpCountry.cl_nameOfCountry);
		indexOfOurCountry = cl_ourArray.size();
		cl_ourArray.push_back(tmpCountry);

		cl_isChanged = true;
		result = true;
	}

	if (cl_ourArray[indexOfOurCountry].AddByISBN(currentISBN))
	{
		cl_isChanged = true;
		return true;
	}

	return result;
}
/*
void CountryDBClass::Update()
{
	DefaultDB<OneElementOf::Country>::Update();
}

void CountryDBClass::Delete()
{
	DefaultDB<OneElementOf::Country>::Delete();
}
*//*
OneElementOf::Country& CountryDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Country& CountryDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Country& CountryDBClass::operator[](int index)
{
	return GetElement(index);
}*/

int CountryDBClass::FindByName(const std::string& strToFind)
{
	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].cl_nameOfCountry == strToFind)
		{
			return i;
		}
	}

	return -1;
}

int CountryDBClass::FindByISBNPart(const ISBNOnePart& partToFind)
{
	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].cl_countryISBNPart == partToFind)
		{
			return i;
		}
	}

	return -1;
}

std::string CountryDBClass::GetInfo(const ISBNClass& num)
{
	auto index = FindByISBNPart(num[1]);
	if (index < 0)
	{
		return std::string();
	}

	std::string buffer;
	buffer += "Регион (страна): " + cl_ourArray[index].GetName() + "\n";

	auto publishers = cl_ourArray[index].GetPublishers();

	for(auto it = publishers.begin(); it != publishers.end(); ++it)
	{
		if (it->GetISBNParts().Find(num[2]) >= 0)
		{
			buffer += "Издательство: " + it->GetName() + "\n";
			break;
		}
	}

	return buffer;
}
/*
void CountryDBClass::SomethingIsChanged()
{
	DefaultDB<OneElementOf::Country>::SomethingIsChanged();
}
*/