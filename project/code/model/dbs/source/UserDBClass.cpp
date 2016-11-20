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

void UserDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool UserDBClass::UpdateElement(OneElementOf::User& elem)
{
	ClearConsole();
	bool isUpdated = false;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		//std::cout << "1) Сбросить пароль" << std::endl;
		//std::cout << "2) Изменить права доступа" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;/*
		case '1':
			elem.ResetPassword();
			isUpdated = true;
			break;
		case '2':
			elem.InputNewPrivelege();
			isUpdated = true;
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
*/
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
