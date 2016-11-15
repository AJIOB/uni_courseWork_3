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

void CountryDBClass::Save()
{
	DefaultDB<OneElementOf::Country>::SaveChangesToFile();
}

void CountryDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool CountryDBClass::UpdateElement(OneElementOf::Country& elem)
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть текущий элемент" << std::endl;
		std::cout << "2) Изменить название региона расположения" << std::endl;
		std::cout << "3) Изменить ISBN код региона" << std::endl;
		std::cout << "4) Поработать с издательствами" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			std::cout << elem << std::endl;
			break;
		case '2':
			if (elem.InputNewName()) isUpdated = true;
			break;
		case '3':
			if (elem.InputNewISBNPart()) isUpdated = true;
			break;
		case '4':
			if (elem.WorkWithPublishers()) isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

void CountryDBClass::Unload()
{
	WriteAllIfNeed();
}

void CountryDBClass::Add()
{
	DefaultDB<OneElementOf::Country>::Add(true);
}

void CountryDBClass::Show() const
{
	DefaultDB<OneElementOf::Country>::Show();
}

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

void CountryDBClass::Update()
{
	DefaultDB<OneElementOf::Country>::Update();
}

void CountryDBClass::Delete()
{
	DefaultDB<OneElementOf::Country>::Delete();
}

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
}

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

void CountryDBClass::SomethingIsChanged()
{
	DefaultDB<OneElementOf::Country>::SomethingIsChanged();
}
