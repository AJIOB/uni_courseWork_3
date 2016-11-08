#include "../headers/CountryDBClass.h"

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
		/*std::cout << "1) Поработать с ISBN частями" << std::endl;
		std::cout << "2) Изменить название" << std::endl;
		std::cout << "3) Изменить страну расположения" << std::endl;
		std::cout << "4) Изменить город расположения" << std::endl;
		*/std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		/*case '1':
			if (elem.WorkWithISBNCountryPart())
			{
				isUpdated = true;
			}
			break;
		case '2':
			if (elem.InputNewName()) isUpdated = true;
			break;
		case '3':
			if (elem.InputNewCountry()) isUpdated = true;
			break;
		case '4':
			if (elem.InputNewCity()) isUpdated = true;
			break;*/
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
	DefaultDB<OneElementOf::Country>::Add();
}

void CountryDBClass::Show() const
{
	DefaultDB<OneElementOf::Country>::Show();
}

int CountryDBClass::FindByISBNPart(const uli& currentISBN) const
{/*
	OneElementOf::Country tmp(this);
	tmp.cl_countryISBNPart = currentISBN;

	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].EqualByISBNPart(tmp))
		{
			return i;
		}
	}*/

	return -1;
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

void CountryDBClass::SomethingIsChanged()
{
	cl_isChanged = true;
}
