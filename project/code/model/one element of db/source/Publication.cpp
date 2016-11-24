#include "../headers/Publication.h"
#include "../../dbs/headers/PublicationDBClass.h"

std::ostream& OneElementOf::operator<<(std::ostream& s, const Publication& that)
{
	s << "ISBN: " << that.cl_ISBN.GetAsString() << std::endl;
	s << "Название издания: " << that.cl_name << std::endl;
	s << "Авторы: " << that.cl_authors << std::endl;
	s << "Год издания: " << that.cl_yearOfPublication <<std::endl;

	auto parent = that.GetConnectedCountryDB();
	if (parent)
	{
		s << (parent->GetInfo(that.cl_ISBN));
	}

	if (that.cl_userTags.size() > 0)
	{
		s << "Пользовательские метки:" <<std::endl;
		s << that.cl_userTags;
	}

	/*
	int index = that.GetConnectedCopiesDB()->FindByISBN(that.cl_ISBN);
	if (index < 0)
	{
		s << "В библиотеке отсутствуют экземпляры данной книги" << std::endl;
	}
	else
	{
		s << that.GetConnectedCopiesDB()[0][index] << std::endl;
	}*/

	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Publication& that)
{
	do
	{
		OutputConsole("Введите ISBN:");
		Stream::Input(that.cl_ISBN);
		if (that.GetConnectedCountryDB())
		{
			that.GetConnectedCountryDB()->AddByISBN(that.cl_ISBN);
		}

		if (!(that.cl_parent) || (that.cl_parent->FindByISBN(that.cl_ISBN) < 0))
		{
			break;
		}

		if (Stream::GetOnlyYN("Данное издание уже имеется. Отменить ввод?") == 'Y')
		{
			throw RepeatException();
		}
	}
	while (true);

	OutputConsole("Введите название издания:");
	Stream::Input(that.cl_name);
	OutputConsole("Введите авторов:");
	Stream::Input(that.cl_authors);
	OutputConsole("Введите год издания:");
	Stream::Input(that.cl_yearOfPublication);

	return s;
}

void OneElementOf::Publication::BWrite(const bString& bInfo, strPos& it)
{
	Publication buffer(cl_parent);

	buffer.cl_ISBN = ISBNClass(bInfo, it);
	buffer.cl_name = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_authors = BStringIO::ReadBInfo<std::string>(bInfo, it);
	buffer.cl_yearOfPublication = BStringIO::ReadBInfo<uli>(bInfo, it);
	buffer.cl_userTags.BWrite(bInfo, it);
	
	(*this) = buffer;
}

CountryDBClass* OneElementOf::Publication::GetConnectedCountryDB() const
{
	if (!cl_parent)
	{
		return nullptr;
	}

	return (cl_parent->cl_connected_CountryDB);
}
/*
CopiesDBClass* OneElementOf::Publication::GetConnectedCopiesDB() const
{
	return cl_parent->cl_connected_CopiesDB;
}*/

OneElementOf::Publication::Publication(void* parent)
{
	cl_yearOfPublication = 0;

	cl_parent = reinterpret_cast<PublicationDBClass*> (parent);
	//cl_countryISBNPart = -1;
}

OneElementOf::Publication::Publication(const Publication& that)
{
	(*this) = that;
}

OneElementOf::Publication::Publication(const bString& bInfo, strPos& it, void* parent)
{
	cl_parent = reinterpret_cast<PublicationDBClass*> (parent);
	BWrite(bInfo, it);
}

OneElementOf::Publication::~Publication()
{
}

OneElementOf::Publication& OneElementOf::Publication::operator=(const Publication& that)
{
	cl_ISBN = that.cl_ISBN;
	cl_name = that.cl_name;
	cl_authors = that.cl_authors;
	cl_yearOfPublication = that.cl_yearOfPublication;
	cl_userTags = that.cl_userTags;

	cl_parent = that.cl_parent;

	return (*this);
}

ISBNClass OneElementOf::Publication::GetISBN() const
{
	return cl_ISBN;
}

std::string OneElementOf::Publication::GetName() const
{
	return cl_name;
}

std::string OneElementOf::Publication::GetAuthor() const
{
	return cl_authors;
}

uli OneElementOf::Publication::GetYearOfPublication() const
{
	return cl_yearOfPublication;
}

MyContainer<std::string> OneElementOf::Publication::GetUserTags() const
{
	return cl_userTags;
}

bString OneElementOf::Publication::BRead() const
{
	return (cl_ISBN.BRead() + BStringIO::MakeBString(cl_name) + BStringIO::MakeBString(cl_authors) + BStringIO::MakeBString(cl_yearOfPublication) + cl_userTags.BRead());
}

bool OneElementOf::Publication::EqualByISBN(const Publication& that) const
{
	return (cl_ISBN == that.cl_ISBN);
}

bool OneElementOf::Publication::operator==(const Publication& that) const
{
	return EqualByISBN(that);
}

bool OneElementOf::Publication::operator<(const Publication& that) const
{
	return (cl_ISBN < that.cl_ISBN);
}

bool OneElementOf::Publication::operator>(const Publication& that) const
{
	return (cl_ISBN > that.cl_ISBN);
}

bool OneElementOf::Publication::InputNewISBN()
{
	Publication buffer(*this);
	do
	{
		do
		{
			OutputConsole("Введите новое название издания.");
			Stream::Input(buffer.cl_ISBN);

			if (cl_parent->FindByISBN(buffer.cl_ISBN) < 0)
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

bool OneElementOf::Publication::InputNewName()
{
	Publication buffer(*this);
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

bool OneElementOf::Publication::InputNewAuthor()
{
	Publication buffer(*this);
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

bool OneElementOf::Publication::InputNewYear()
{
	Publication buffer(*this);
	do
	{
		OutputConsole("Введите новый год издания.");
		Stream::Input(buffer.cl_yearOfPublication);
		OutputConsole("Измененный элемент:");
		std::cout << buffer;
	} while (Stream::GetOnlyYN("Всё ли введено правильно?") == 'N');

	(*this) = buffer;
	return true;
}

bool OneElementOf::Publication::WorkWithTags()
{
	return cl_userTags.OperationsWithElements();
}

bool OneElementOf::Publication::UpdateMe()
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть текущий элемент" << std::endl;
		std::cout << "2) Изменить ISBN издания" << std::endl;
		std::cout << "3) Изменить название издания" << std::endl;
		std::cout << "4) Изменить авторов" << std::endl;
		std::cout << "5) Изменить год издания" << std::endl;
		std::cout << "6) Поработать с пользовательскими метками" << std::endl;
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
			if (this->InputNewISBN()) isUpdated = true;
			break;
		case '3':
			if (this->InputNewName()) isUpdated = true;
			break;
		case '4':
			if (this->InputNewAuthor()) isUpdated = true;
			break;
		case '5':
			if (this->InputNewYear()) isUpdated = true;
			break;
		case '6':
			if (this->WorkWithTags()) isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

/*
void OneElementOf::Publication::InputElem(bool ISBNIsGettedByParametr, const ISBNClass ISBN)
{
	if (!ISBNIsGettedByParametr)
	{
		OutputConsole("Введите ISBN:");
		Stream::Input(this->cl_ISBN);
	}
	else
	{
		cl_ISBN = ISBN;
	}

	this->GetConnectedCountryDB()->AddByISBN(this->cl_ISBN);
	OutputConsole("Введите название издания:");
	Stream::Input(this->cl_name);
	OutputConsole("Введите авторов:");
	Stream::Input(this->cl_authors);
	OutputConsole("Введите год издания:");
	Stream::Input(this->cl_yearOfPublication);
}
*/
