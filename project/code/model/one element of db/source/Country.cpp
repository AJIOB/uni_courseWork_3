#include "../headers/Country.h"
#include "../../dbs/headers/CountryDBClass.h"

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

	if ((that.cl_parentDB) && (that.cl_parentDB->FindByName(that.cl_nameOfCountry) >= 0))
	{
		return s;
	}

	OutputConsole("Введите ISBN часть кода региона (страны):");
	Stream::Input(that.cl_countryISBNPart);
	
	if ((that.cl_parentDB) && (that.cl_parentDB->FindByISBNPart(that.cl_countryISBNPart) >= 0))
	{
		return s;
	}

	OutputConsole("Введите издательство региона (страны):");
	Stream::Input(that.cl_publishers);
	return s;
}

void OneElementOf::Country::BWrite(const bString& bInfo, strPos& it)
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

bool OneElementOf::Country::AddByISBN(const ISBNClass& num)
{
	if (cl_countryISBNPart != num[1])
	{
		return false;
	}

	//ищем, а вдруг есть уже такой номер
	for (auto it1 = cl_publishers.begin(); it1 != cl_publishers.end(); ++it1)
	{
		for (auto it2 = it1->cl_ISBN_PublisherPart.begin(); it2 != it1->cl_ISBN_PublisherPart.end(); ++it2)
		{
			if ((*it2) == num[2])
			{
				return false;
			}
		}
	}

	OneElementOf::Publisher tmpPublisher;
	OutputConsole("Введите название издательства:");
	Stream::Input(tmpPublisher.cl_name);
	OutputConsole("Введите город расположения издательства:");
	Stream::Input(tmpPublisher.cl_city);

	int indexOfPublisher = cl_publishers.Find(tmpPublisher);
	if (indexOfPublisher < 0)
	{
		indexOfPublisher = cl_publishers.size();
		cl_publishers.push_back(tmpPublisher);
	}

	cl_publishers[indexOfPublisher].cl_ISBN_PublisherPart.push_back(num[2]);
	return true;
}

OneElementOf::Country& OneElementOf::Country::GetParentElement(const int index) const
{
	if ((index < 0) || (index >= cl_parentDB->cl_ourArray.size()))
	{
		throw RangeException();
	}

	return (cl_parentDB->cl_ourArray[index]);
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

OneElementOf::Country::Country(const bString& bInfo, strPos& it, void* parentDB) : cl_countryISBNPart()
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

std::string OneElementOf::Country::GetName() const
{
	return cl_nameOfCountry;
}

ISBNOnePart OneElementOf::Country::GetISBNPart() const
{
	return cl_countryISBNPart;
}

MyContainer<OneElementOf::Publisher> OneElementOf::Country::GetPublishers() const
{
	return cl_publishers;
}

bString OneElementOf::Country::BRead() const
{
	return (BStringIO::MakeBString(cl_nameOfCountry) + BStringIO::MakeBString(cl_countryISBNPart) + cl_publishers.BRead());
}

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

bool OneElementOf::Country::WorkWithPublishers()
{
	return cl_publishers.OperationsWithElements();
}

int OneElementOf::Country::FindByName(const std::string& name)
{
	for (auto i = 0; i < cl_publishers.size(); ++i)
	{
		if (cl_publishers[i].cl_name == name)
		{
			return i;
		}
	}

	return  -1;
}



bool OneElementOf::Country::EqualByISBNPart(const Country& that) const
{
	return (cl_countryISBNPart == that.cl_countryISBNPart);
}

bool OneElementOf::Country::operator==(const Country& that) const
{
	return EqualByISBNPart(that);
}

bool OneElementOf::Country::operator<(const Country& that) const
{
	return (cl_countryISBNPart.GetString() < that.cl_countryISBNPart.GetString());
}

bool OneElementOf::Country::operator>(const Country& that) const
{
	return (cl_countryISBNPart.GetString() > that.cl_countryISBNPart.GetString());
}

bool OneElementOf::Country::UpdateMe()
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
			std::cout << *this << std::endl;
			break;
		case '2':
			if (InputNewName()) isUpdated = true;
			break;
		case '3':
			if (InputNewISBNPart()) isUpdated = true;
			break;
		case '4':
			if (WorkWithPublishers()) isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}
