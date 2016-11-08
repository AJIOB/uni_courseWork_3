#include "../headers/Publisher.h"
#include "../../binary input&output/templates/BStringIO.h"

std::ostream& OneElementOf::operator<<(std::ostream& s, const Publisher& that)
{
	s << "Название: " << that.cl_name << std::endl;
	s << "Город: " << that.cl_city << std::endl;
	s << "ISBN коды издательства: " << that.cl_ISBN_PublisherPart <<std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Publisher& that)
{
	OutputConsole("Введите название:");
	Stream::Input(that.cl_name);
	OutputConsole("Введите город дислокации:");
	Stream::Input(that.cl_city);
	OutputConsole("Введите ISBN код издательства:");
	Stream::Input(that.cl_ISBN_PublisherPart);

	return s;
}

void OneElementOf::Publisher::BWrite(const std::string& bInfo, strPos& it)
{
	Publisher buffer(cl_parent);
	buffer.cl_name = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_city = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_ISBN_PublisherPart.BWrite(bInfo, it);
	
	(*this) = buffer;
}

OneElementOf::Publisher::Publisher(void* parent)
{
	cl_parent = reinterpret_cast<Country*> (parent);
	//cl_countryISBNPart = -1;
}

OneElementOf::Publisher::Publisher(const Publisher& that)
{
	(*this) = that;
}

OneElementOf::Publisher::Publisher(const std::string& bInfo, strPos& it, void* parent)
{
	cl_parent = reinterpret_cast<Country*> (parent);
	BWrite(bInfo, it);
}

OneElementOf::Publisher::~Publisher()
{
}

OneElementOf::Publisher& OneElementOf::Publisher::operator=(const Publisher& that)
{
	cl_name = that.cl_name;
	cl_city = that.cl_city;
	cl_ISBN_PublisherPart = that.cl_ISBN_PublisherPart;
	cl_parent = that.cl_parent;
	return (*this);
}

std::string OneElementOf::Publisher::BRead() const
{
	return (BStringIO::GetBString(cl_name) + BStringIO::GetBString(cl_city) + cl_ISBN_PublisherPart.BRead());
}

bool OneElementOf::Publisher::WorkWithISBNPublisherPart()
{
	return cl_ISBN_PublisherPart.OperationsWithElements();
}

bool OneElementOf::Publisher::InputNewName()
{
	Publisher buffer(*this);
	do
	{
		OutputConsole("Введите новое название.");
		Stream::Input(buffer.cl_name);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}
/*
bool OneElementOf::Publisher::InputNewCountry()
{
	Publisher buffer(*this);
	do
	{
		OutputConsole("Введите новый ISBN страны.");
		//Stream::Input(buffer.cl_countryISBNPart);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}*/

bool OneElementOf::Publisher::InputNewCity()
{
	Publisher buffer(*this);
	do
	{
		OutputConsole("Введите новый город расположения.");
		Stream::Input(buffer.cl_city);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}
