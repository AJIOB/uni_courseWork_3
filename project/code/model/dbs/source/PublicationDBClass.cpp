#include "../headers/PublicationDBClass.h"

PublicationDBClass::PublicationDBClass(CountryDBClass* dbToConnect, bool isReadOnly)
	: DefaultDB<OneElementOf::Publication>(PublicationDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
	cl_connected_CountryDB = dbToConnect;
}

PublicationDBClass::~PublicationDBClass()
{
	Unload();
}

void PublicationDBClass::Save()
{
	DefaultDB<OneElementOf::Publication>::SaveChangesToFile();
}

void PublicationDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool PublicationDBClass::UpdateElement(OneElementOf::Publication& elem)
{//TODO
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
		std::cout << "0) Назад" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			std::cout << elem << std::endl;
			break;
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
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);

	//return false;
}

void PublicationDBClass::Unload()
{
	WriteAllIfNeed();
}

void PublicationDBClass::Add()
{
	DefaultDB<OneElementOf::Publication>::Add(true);
}

void PublicationDBClass::Show() const
{
	DefaultDB<OneElementOf::Publication>::Show();
}

void PublicationDBClass::Update()
{
	DefaultDB<OneElementOf::Publication>::Update();
}

void PublicationDBClass::Delete()
{
	DefaultDB<OneElementOf::Publication>::Delete();
}

OneElementOf::Publication& PublicationDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Publication& PublicationDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Publication& PublicationDBClass::operator[](int index)
{
	return GetElement(index);
}

void PublicationDBClass::SomethingIsChanged()
{
	DefaultDB<OneElementOf::Publication>::SomethingIsChanged();
}

int PublicationDBClass::FindByISBNPart(const ISBNClass& ISBNToFind)
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
