#include "../headers/LoginDBClass.h"

LoginDBClass::LoginDBClass(bool isReadOnly)
	: CryptedDB<OneElementOf::Auth>(LoginDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
}

LoginDBClass::~LoginDBClass()
{
	Unload();
}

void LoginDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

void LoginDBClass::UpdateElementWithIndex(int goodIndexOnly)
{

}

void LoginDBClass::Unload()
{
	WriteAllIfNeed();
}

void LoginDBClass::Add()
{
	CryptedDB<OneElementOf::Auth>::Add();
}

void LoginDBClass::Show() const
{
	CryptedDB<OneElementOf::Auth>::Show();
}

int LoginDBClass::Find(const OneElementOf::Auth& currLP) const
{
	for (auto i = 0; i < cl_ourArray.size(); ++i)
	{
		if (cl_ourArray[i].EqualByAll(currLP))
		{
			return i;
		}
	}

	return -1;
}

void LoginDBClass::Update()
{
	CryptedDB<OneElementOf::Auth>::Update();
}

void LoginDBClass::Delete()
{
	CryptedDB<OneElementOf::Auth>::Delete();
}

OneElementOf::Auth& LoginDBClass::Get(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Auth& LoginDBClass::Get(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Auth& LoginDBClass::operator[](int index)
{
	return Get(index);
}
