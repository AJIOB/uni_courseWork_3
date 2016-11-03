#include "../headers/LoginDBClass.h"

LoginDBClass::LoginDBClass(bool isReadOnly)
	: CryptedDB<OneElementOf::Auth>(LoginDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	//Load();
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
