#include "../headers/Publisher.h"
//#include "../../binary input&output/templates/BStringIO.h"

std::ostream& OneElementOf::operator<<(std::ostream& s, const Publisher& that)
{
	s << "Название: " << that.cl_name << std::endl;
	s << "Город: " << that.cl_city << std::endl;
	s << "ISBN коды издательства: " << that.cl_ISBN_PublisherPart <<std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Publisher& that)
{
	OutputConsole("Введите название издательства:");
	Stream::Input(that.cl_name);
	OutputConsole("Введите город дислокации:");
	Stream::Input(that.cl_city);
	OutputConsole("Введите ISBN код издательства:");
	Stream::Input(that.cl_ISBN_PublisherPart);

	return s;
}

void OneElementOf::Publisher::BWrite(const bString& bInfo, strPos& it)
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

OneElementOf::Publisher::Publisher(const bString& bInfo, strPos& it, void* parent)
{
	cl_parent = reinterpret_cast<Country*> (parent);
	BWrite(bInfo, it);
}

OneElementOf::Publisher::~Publisher()
{
}

bool OneElementOf::Publisher::AddISBNPart(const ISBNOnePart& newISBNPart)
{
	cl_ISBN_PublisherPart.push_back(newISBNPart);
	return true;
}

OneElementOf::Publisher& OneElementOf::Publisher::operator=(const Publisher& that)
{
	cl_name = that.cl_name;
	cl_city = that.cl_city;
	cl_ISBN_PublisherPart = that.cl_ISBN_PublisherPart;
	cl_parent = that.cl_parent;
	return (*this);
}

std::string OneElementOf::Publisher::GetName() const
{
	return cl_name;
}

std::string OneElementOf::Publisher::GetCity() const
{
	return cl_city;
}

MyContainer<ISBNOnePart> OneElementOf::Publisher::GetISBNParts() const
{
	return cl_ISBN_PublisherPart;
}

bString OneElementOf::Publisher::BRead() const
{
	return (BStringIO::MakeBString(cl_name) + BStringIO::MakeBString(cl_city) + cl_ISBN_PublisherPart.BRead());
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

bool OneElementOf::Publisher::WorkWithISBNPart()
{
	return cl_ISBN_PublisherPart.OperationsWithElements();
}

bool OneElementOf::Publisher::EqualByName(const Publisher& that) const
{
	return (this->cl_name == that.cl_name);
}

bool OneElementOf::Publisher::EqualByNameAndCity(const Publisher& that) const
{
	return ((this->cl_name == that.cl_name) && (this->cl_city == that.cl_city));
}

bool OneElementOf::Publisher::EqualByISBNPart(const ISBNOnePart& ISBNpart) const
{
	if (this->cl_ISBN_PublisherPart.Find(ISBNpart) >= 0)
	{
		return true;
	}
	return false;
}

bool OneElementOf::Publisher::operator==(const Publisher& that) const
{
	return EqualByNameAndCity(that);
}

bool OneElementOf::Publisher::operator>(const Publisher& that) const
{
	return ((cl_name > that.cl_name) || ((cl_name == that.cl_name) && (cl_city > that.cl_city)));
}

bool OneElementOf::Publisher::operator<(const Publisher& that) const
{
	return ((cl_name < that.cl_name) || ((cl_name == that.cl_name) && (cl_city < that.cl_city)));
}

bool OneElementOf::Publisher::UpdateMe()
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть элемент" << std::endl;
		std::cout << "2) Изменить название издательства" << std::endl;
		std::cout << "3) Изменить город расположения издательства" << std::endl;
		std::cout << "4) Поработать с ISBN идентификаторами издательства" << std::endl;
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			std::cout << *this << std::endl;
			break;
		case '2':
			if (this->InputNewName()) isUpdated = true;
			break;
		case '3':
			if (this->InputNewCity()) isUpdated = true;
			break;
		case '4':
			if (this->WorkWithISBNPublisherPart()) isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}
