#include "../headers/IsPublicationGetted.h"

void IsPublicationGetted::BWrite(const bString& bInfo, strPos& it)
{
	//TODO
}

IsPublicationGetted::IsPublicationGetted() : cl_whoIsGet()
{
	cl_isArcheved = false;
	cl_isGetted = false;
}

IsPublicationGetted::IsPublicationGetted(const IsPublicationGetted& that)
{
	(*this) = that;
}

IsPublicationGetted::IsPublicationGetted(const bString& bInfo, strPos& it)
{
	BWrite(bInfo, it);
}

IsPublicationGetted::~IsPublicationGetted()
{
}

IsPublicationGetted& IsPublicationGetted::operator=(const IsPublicationGetted& that)
{
	cl_isArcheved = that.cl_isArcheved;
	cl_isGetted = that.cl_isGetted;
	cl_whoIsGet = that.cl_whoIsGet;

	return (*this);
}

std::string IsPublicationGetted::BRead() const
{
	//TODO
	return (BStringIO::MakeBString(cl_isArcheved) + BStringIO::MakeBString(cl_isGetted) + cl_whoIsGet.BRead());//);
}

bool IsPublicationGetted::GetIsArchieved() const
{
	return cl_isArcheved;
}

bool IsPublicationGetted::GetIsGetted() const
{
	return cl_isGetted;
}

DefaultID IsPublicationGetted::GetWhoIsGet() const
{
	return cl_whoIsGet;
}

bool IsPublicationGetted::Archieve()
{
	if (cl_isGetted)
	{
		return false;
	}

	cl_isArcheved = true;
	return true;
}

bool IsPublicationGetted::GetTo(const DefaultID& person)
{
	if (cl_isArcheved || cl_isGetted)
	{
		return false;
	}

	cl_whoIsGet = person;

	return true;
}

bool IsPublicationGetted::UpdateMe()
{
	ClearConsole();
	bool isUpdated = false;

	do
	{
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Просмотреть элемент" << std::endl;
		std::cout << "2) Архивировать этот экземпляр" << std::endl;
		std::cout << "3) Вернуть экземпляр из архива" << std::endl;
		std::cout << "TODO 4) Выдать пользователю этот экземпляр" << std::endl;
		std::cout << "TODO 5) Вернуть экземпляр от пользователя" << std::endl;
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
			if (this->Archieve()) isUpdated = true;
			else
			{
				OutputConsole("Невозможно отправить экземпляр в архив. Возможно, книгу не вернули в библиотеку");
			}
			break;
		case '3':
			if (!cl_isArcheved)
			{
				OutputConsole("Невозможно вернуть экземпляр из архива. Книга не в архиве");
				break;
			}
			if (cl_isArcheved)
			{
				cl_isArcheved = false;
			}
			isUpdated = true;
			break;
		case '4':
			//if (this->GetTo()) isUpdated = true;
			break;
		case '5':
			//if (this->WorkWithISBNPublisherPart()) isUpdated = true;
			break;
		
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
}

std::ostream& operator<<(std::ostream& s, const IsPublicationGetted& elem)
{
	s << "Издание в архиве: " /*<< _IOSboolalpha*/ << elem.cl_isArcheved << std::endl;
	if (elem.cl_isArcheved)
	{
		return s;
	}

	s << "Издание выдано: " << elem.cl_isGetted << std::endl;
	if (!elem.cl_isGetted)
	{
		return s;
	}

	s << "Выдано пользователю: " << elem.cl_whoIsGet.GetID() << std::endl;

	return s;
}
