#include "../headers/Country.h"

std::ostream& OneElementOf::operator<<(std::ostream& s, const Country& that)
{
	s << "Название региона (страны): " << that.cl_nameOfCountry << std::endl;
	s << "ISBN часть кода региона (страны): " << that.cl_countryISBNPart <<std::endl;
	s << "Издательства региона: " << that.cl_publishers << std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Country& that)
{
	OutputConsole("Введите название региона (страны):");
	Stream::Input(that.cl_nameOfCountry);
	OutputConsole("Введите ISBN часть кода региона (страны):");
	Stream::Input(that.cl_countryISBNPart);
	OutputConsole("Введите издательство региона (страны):");
	Stream::Input(that.cl_publishers);
	return s;
}

void OneElementOf::Country::BWrite(const std::string& bInfo, strPos& it)
{
	Country buffer(cl_parentDB);
	buffer.cl_nameOfCountry = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_countryISBNPart = BStringIO::ReadBInfo<ISBNOnePart>(bInfo, it);
	buffer.cl_publishers.BWrite(bInfo, it);

	for (auto i = buffer.cl_publishers.begin(); i != buffer.cl_publishers.end(); ++i)
	{
		i->cl_parent = this;
	}

	(*this) = buffer;
}

OneElementOf::Country::Country(void* parentDB) : cl_countryISBNPart()
{
	cl_parentDB = reinterpret_cast<CountryDBClass*> (parentDB);
	//cl_countryISBNPart = -1;
}

OneElementOf::Country::Country(const Country& that)
{
	(*this) = that;
}

OneElementOf::Country::Country(const std::string& bInfo, strPos& it, void* parentDB) : cl_countryISBNPart()
{
	cl_parentDB = reinterpret_cast<CountryDBClass*> (parentDB);
	BWrite(bInfo, it);
}

OneElementOf::Country::~Country()
{
}

OneElementOf::Country& OneElementOf::Country::operator=(const Country& that)
{
	cl_nameOfCountry = that.cl_nameOfCountry;
	cl_countryISBNPart = that.cl_countryISBNPart;
	cl_publishers = that.cl_publishers;
	cl_parentDB = that.cl_parentDB;
	return (*this);
}

std::string OneElementOf::Country::BRead()
{
	return (BStringIO::GetBString(cl_nameOfCountry) + BStringIO::GetBString(cl_countryISBNPart) + cl_publishers.BRead());
}
/*
bool OneElementOf::Country::WorkWithISBNCountryPart()
{
	return cl_ISBN_CountryPart.OperationsWithElements();
}*/

bool OneElementOf::Country::InputNewName()
{
	Country buffer(*this);
	do
	{
		OutputConsole("Введите новую страну расположения.");
		Stream::Input(buffer.cl_nameOfCountry);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Country::InputNewISBNPart()
{
	Country buffer(*this);
	do
	{
		OutputConsole("Введите новую ISBN часть.");
		Stream::Input(buffer.cl_countryISBNPart);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Country::EqualByISBNPart(const Country& that) const
{
	return (cl_countryISBNPart == that.cl_countryISBNPart);
}
