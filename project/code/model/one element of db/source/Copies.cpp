#include "../headers/Copies.h"
#include "../../dbs/headers/CopiesDBClass.h"

std::ostream& OneElementOf::operator<<(std::ostream& s, const Copies& that)
{
	auto connectedPublicationDB = that.GetConnectedPublicationDB();

	int findIndex = -1;

	if (connectedPublicationDB)
	{
		findIndex = connectedPublicationDB->FindByISBN(that.cl_ISBN);
	}

	if (findIndex < 0)
	{
		s << "ISBN: " << that.cl_ISBN << std::endl;
	}
	else if (that.GetConnectedPublicationDB())
	{
		s << that.GetConnectedPublicationDB()[0][findIndex];
	}

	s << "Всего " << that.CopiesThatNotArchieved() << " экземпляров (-а)" << std::endl;
	s << "В наличии " << that.CopiesYouCanGetNow() << " экземпляров (-а)" << std::endl;
	return s;
}

std::istream& OneElementOf::operator>>(std::istream& s, Copies& that)
{
	Copies buff(that);

	auto parent = that.cl_parent;

	do
	{
		OutputConsole("Введите ISBN:");
		Stream::Input(buff.cl_ISBN);

		int findIndex = -1;

		if (parent)
		{
			findIndex = that.cl_parent->FindByISBN(buff.cl_ISBN);
		}

		if (findIndex < 0)
		{
			break;
		}

		if (Stream::GetOnlyYN("Был введен ISBN, который уже есть в этой базе. Отменить ввод?") == 'Y')
		{
			return s;
		}
		
		OutputConsole("Пожалуйста, введите уникальный ISBN или выберите другую операцию");
	} while (true);

	uli iBuffer;
	OutputConsole("Введите количество экземпляров издания:");
	Stream::Input(iBuffer);
	buff.cl_isThisCopyGetted.resize(iBuffer);

	that = buff;

	return s;
}

void OneElementOf::Copies::BWrite(const bString& bInfo, strPos& it)
{
	Copies buffer(cl_parent);

	buffer.cl_ISBN = ISBNClass(bInfo, it);
	buffer.cl_isThisCopyGetted.BWrite(bInfo, it);
	(*this) = buffer;
}

int OneElementOf::Copies::CopiesThatNotArchieved() const
{
	int num = 0;
	
	for (auto it = cl_isThisCopyGetted.begin(); it != cl_isThisCopyGetted.end(); ++it)
	{
		if (!(it->GetIsArchieved()))
		{
			num++;
		}
	}

	return num;
}

int OneElementOf::Copies::CopiesYouCanGetNow() const
{
	int num = 0;
	
	for (auto it = cl_isThisCopyGetted.begin(); it != cl_isThisCopyGetted.end(); ++it)
	{
		if ((!(it->GetIsArchieved())) && (!(it->GetIsGetted())))
		{
			num++;
		}
	}

	return num;
}

PublicationDBClass* OneElementOf::Copies::GetConnectedPublicationDB() const
{
	if (!cl_parent)
	{
		return nullptr;
	}

	return cl_parent->cl_connected_PublicationDB;
}

/*
CountryDBClass* OneElementOf::Copies::GetConnectedCountryDB() const
{
	return (cl_parent->cl_connected_CountryDB);
}*/

OneElementOf::Copies::Copies(void* parent)
{

	cl_parent = reinterpret_cast<CopiesDBClass*> (parent);
}

OneElementOf::Copies::Copies(const Copies& that)
{
	(*this) = that;
}

OneElementOf::Copies::Copies(const bString& bInfo, strPos& it, void* parent)
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
	cl_isThisCopyGetted = that.cl_isThisCopyGetted;

	cl_parent = that.cl_parent;

	return (*this);
}

ISBNClass OneElementOf::Copies::GetISBN() const
{
	return cl_ISBN;
}

MyContainer<IsPublicationGetted> OneElementOf::Copies::GetArrayOfInfoAboutCopies() const
{
	return cl_isThisCopyGetted;
}

bString OneElementOf::Copies::BRead() const
{
	return (cl_ISBN.BRead() + cl_isThisCopyGetted.BRead());
}

bool OneElementOf::Copies::EqualByISBN(const Copies& that) const
{
	return (cl_ISBN == that.cl_ISBN);
}

bool OneElementOf::Copies::operator==(const Copies& that) const
{
	return EqualByISBN(that);
}

bool OneElementOf::Copies::operator<(const Copies& that) const
{
	return (cl_ISBN < that.cl_ISBN);
}

bool OneElementOf::Copies::operator>(const Copies& that) const
{
	return (cl_ISBN > that.cl_ISBN);
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

			if (cl_parent && (cl_parent->FindByISBN(buffer.cl_ISBN) < 0))
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

bool OneElementOf::Copies::WorkWithCopies()
{
	return cl_isThisCopyGetted.Update();
}

bool OneElementOf::Copies::UpdateMe()
{
	//TODO: we need update

	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть текущий элемент" << std::endl;/*
		std::cout << "2) Изменить ISBN издания" << std::endl;
		std::cout << "3) Изменить название издания" << std::endl;
		std::cout << "4) Изменить авторов" << std::endl;
		std::cout << "5) Изменить год издания" << std::endl;
		std::cout << "6) Поработать с пользовательскими метками" << std::endl;*/
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			std::cout << *this << std::endl;
			break;/*
		case '2':
			if (elem.InputNewISBN()) isUpdated = true;
			break;
		case '3':
			if (elem.InputNewName()) isUpdated = true;
			break;
		case '4':
			if (elem.InputNewAuthor()) isUpdated = true;
			break;
		case '5':
			if (elem.InputNewYear()) isUpdated = true;
			break;
		case '6':
			if (elem.WorkWithTags()) isUpdated = true;
			break;*/
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

/*
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