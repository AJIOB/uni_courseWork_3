#include "../headers/UserDBClass.h"

UserDBClass::UserDBClass(bool isReadOnly)
	: CryptedDB<OneElementOf::User>(UserDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
}

UserDBClass::~UserDBClass()
{
	Unload();
}

uli UserDBClass::GetNewID() const
{
	if (cl_ourArray.size() == 0)
	{
		return 1;
	}

	return (cl_ourArray.back().GetLogin().GetID() + 1);
}

int UserDBClass::FindByAuthInfo(const DefaultID& login, const std::string& password) const
{
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		if (it->GetLogin().EqualByID(login) && (it->CheckPassword(password)))
		{
			return (it - cl_ourArray.begin());
		}
	}

	return -1;
}

int UserDBClass::FindByAuthInfo(const OneElementOf::User& checkedUser) const
{
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		if (it->EqualByAuth(checkedUser))
		{
			return (it - cl_ourArray.begin());
		}
	}

	return -1;
}

void UserDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

/*
void UserDBClass::Unload()
{
	WriteAllIfNeed();
}

void UserDBClass::Add()
{
	CryptedDB<OneElementOf::User>::Add();
}

void UserDBClass::Show() const
{
	CryptedDB<OneElementOf::User>::Show();
}

int UserDBClass::Find(const OneElementOf::User& currLP) const
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

void UserDBClass::Update()
{
	CryptedDB<OneElementOf::User>::Update();
}

void UserDBClass::Delete()
{
	CryptedDB<OneElementOf::User>::Delete();
}
*//*
OneElementOf::User& UserDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::User& UserDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::User& UserDBClass::operator[](int index)
{
	return GetElement(index);
}

void UserDBClass::SomethingIsChanged()
{
	CryptedDB<OneElementOf::User>::SomethingIsChanged();
}
*/