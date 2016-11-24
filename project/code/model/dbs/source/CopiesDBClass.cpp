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
/*
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
}*/
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
