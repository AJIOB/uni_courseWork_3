#include "../headers/Copies.h"
/*
std::ostream& OneElementOf::operator<<(std::ostream& s, const Copies& that)
{
	s << "ISBN: " << that.cl_ISBN.GetAsString() << std::endl;
	s << "Название издания: " << that.cl_name << std::endl;
	s << "Авторы: " << that.cl_authors << std::endl;
	s << "Год издания: " << that.cl_yearOfCopies <<std::endl;
	s << (that.GetConnectedCountryDB()->GetInfo(that.cl_ISBN));
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Copies& that)
{
	OutputConsole("Введите ISBN:");
	Stream::Input(that.cl_ISBN);
	that.GetConnectedCountryDB()->AddByISBN(that.cl_ISBN);
	OutputConsole("Введите название издания:");
	Stream::Input(that.cl_name);
	OutputConsole("Введите авторов:");
	Stream::Input(that.cl_authors);
	OutputConsole("Введите год издания:");
	Stream::Input(that.cl_yearOfCopies);

	return s;
}

void OneElementOf::Copies::BWrite(const std::string& bInfo, strPos& it)
{
	Copies buffer(cl_parent);

	buffer.cl_ISBN = ISBNClass(bInfo, it);
	buffer.cl_name = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_authors = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_yearOfCopies = BStringIO::ReadBInfo<uli>(bInfo, it);
	
	(*this) = buffer;
}

CountryDBClass* OneElementOf::Copies::GetConnectedCountryDB() const
{
	return (cl_parent->cl_connected_CountryDB);
}

OneElementOf::Copies::Copies(void* parent)
{
	cl_yearOfCopies = 0;

	cl_parent = reinterpret_cast<CopiesDBClass*> (parent);
	//cl_countryISBNPart = -1;
}

OneElementOf::Copies::Copies(const Copies& that)
{
	(*this) = that;
}

OneElementOf::Copies::Copies(const std::string& bInfo, strPos& it, void* parent)
{
	cl_parent = reinterpret_cast<CopiesDBClass*> (parent);
	BWrite(bInfo, it);
}

OneElementOf::Copies::~Copies()
{
}

OneElementOf::Copies& OneElementOf::Copies::operator=(const Copies& that)
{
	cl_ISBN = that.cl_ISBN;
	cl_name = that.cl_name;
	cl_authors = that.cl_authors;
	cl_yearOfCopies = that.cl_yearOfCopies;
	cl_parent = that.cl_parent;

	return (*this);
}

ISBNClass OneElementOf::Copies::GetISBN() const
{
	return cl_ISBN;
}

std::string OneElementOf::Copies::GetName() const
{
	return cl_name;
}

std::string OneElementOf::Copies::GetAuthor() const
{
	return cl_authors;
}

uli OneElementOf::Copies::GetYearOfPublicatiion() const
{
	return cl_yearOfCopies;
}

std::string OneElementOf::Copies::BRead() const
{
	return (cl_ISBN.BRead() + BStringIO::GetBString(cl_name) + BStringIO::GetBString(cl_authors) + BStringIO::GetBString(cl_yearOfCopies));
}

bool OneElementOf::Copies::EqualByISBN(const Copies& that) const
{
	return (cl_ISBN == that.cl_ISBN);
}

bool OneElementOf::Copies::operator==(const Copies& that) const
{
	return EqualByISBN(that);
}

bool OneElementOf::Copies::InputNewISBN()
{
	Copies buffer(*this);
	do
	{
		do
		{
			OutputConsole("Введите новое название издания.");
			Stream::Input(buffer.cl_ISBN);

			if (cl_parent->FindByISBNPart(buffer.cl_ISBN) < 0)
			{
				break;
			}

			OutputConsole("Извините, введенный вами номер уже присутствует или вы ввели старый ISBN номер. Пожалуйста, повторите ввод.");
		} while (true);

		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Copies::InputNewName()
{
	Copies buffer(*this);
	do
	{
		OutputConsole("Введите новое название издания.");
		Stream::Input(buffer.cl_name);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Copies::InputNewAuthor()
{
	Copies buffer(*this);
	do
	{
		OutputConsole("Введите новых авторов.");
		Stream::Input(buffer.cl_authors);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Copies::InputNewYear()
{
	Copies buffer(*this);
	do
	{
		OutputConsole("Введите новый год издания.");
		Stream::Input(buffer.cl_yearOfCopies);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

/*
bool OneElementOf::Copies::WorkWithISBNCopiesPart()
{
	return cl_ISBN_CopiesPart.OperationsWithElements();
}

bool OneElementOf::Copies::InputNewName()
{
	Copies buffer(*this);
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

bool OneElementOf::Copies::InputNewCity()
{
	Copies buffer(*this);
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

bool OneElementOf::Copies::WorkWithISBNPart()
{
	return cl_ISBN_CopiesPart.OperationsWithElements();
}

bool OneElementOf::Copies::EqualByName(const Copies& that) const
{
	return (this->cl_name == that.cl_name);
}

bool OneElementOf::Copies::EqualByNameAndCity(const Copies& that) const
{
	return ((this->cl_name == that.cl_name) && (this->cl_city == that.cl_city));
}

bool OneElementOf::Copies::operator==(const Copies& that) const
{
	return EqualByNameAndCity(that);
}

bool OneElementOf::Copies::UpdateMe()
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		/*std::string cl_name;
	std::string cl_city;
	MyContainer<ISBNOnePart> cl_ISBN_CopiesPart;
		 *
		 *
		 *
		 *
		 */
/*
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
			if (this->WorkWithISBNCopiesPart()) isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);


	return false;
}
*/