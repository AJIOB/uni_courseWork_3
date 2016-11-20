#include "../headers/CopiesDBClass.h"

CopiesDBClass::CopiesDBClass(PublicationDBClass* dbToConnect, bool isReadOnly)
	: DefaultDB<OneElementOf::Copies>(CopiesDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
	cl_connected_PublicationDB = dbToConnect;
}

CopiesDBClass::~CopiesDBClass()
{
	Unload();
}

void CopiesDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool CopiesDBClass::UpdateElement(OneElementOf::Copies& elem)
{
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
			std::cout << elem << std::endl;
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

	//return false;
}

/*
int CopiesDBClass::Add()
{
	return DefaultDB<OneElementOf::Copies>::Add(true);
}

void CopiesDBClass::Show() const
{
	DefaultDB<OneElementOf::Copies>::Show();
}

void CopiesDBClass::Update()
{
	DefaultDB<OneElementOf::Copies>::Update();
}

void CopiesDBClass::Delete()
{
	DefaultDB<OneElementOf::Copies>::Delete();
}*/

OneElementOf::Copies& CopiesDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Copies& CopiesDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Copies& CopiesDBClass::operator[](int index)
{
	return GetElement(index);
}
/*
void CopiesDBClass::SomethingIsChanged()
{
	DefaultDB<OneElementOf::Copies>::SomethingIsChanged();
}*/

int CopiesDBClass::FindByISBN(const ISBNClass& ISBNToFind) const
{
	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].GetISBN() == ISBNToFind)
		{
			return i;
		}
	}

	return -1;
}
