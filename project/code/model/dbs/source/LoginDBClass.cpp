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

void LoginDBClass::Save()
{
	CryptedDB<OneElementOf::Auth>::SaveChangesToFile();
}

void LoginDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool LoginDBClass::UpdateElement(OneElementOf::Auth& elem)
{
	ClearConsole();
	bool isUpdated = false;

	do
	{		
		std::cout << "Выберите, пожалуйста, что вы хотите сделать:" << std::endl;
		std::cout << "1) Сбросить пароль" << std::endl;
		std::cout << "2) Изменить права доступа" << std::endl;
		std::cout << "0) Выход" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = Stream::Get();
		
		switch (k)
		{
		case '0':
			return isUpdated;
		case '1':
			elem.ResetPassword();
			isUpdated = true;
			break;
		case '2':
			elem.InputNewPrivelege();
			isUpdated = true;
			break;
		default:
			OutputWarning("Извините, такого варианта не существует. Пожалуйста, повторите выбор");
		}

		PauseConsole();
		ClearConsole();
	}
	while (true);
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

OneElementOf::Auth& LoginDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Auth& LoginDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Auth& LoginDBClass::operator[](int index)
{
	return GetElement(index);
}

void LoginDBClass::SomethingIsChanged()
{
	CryptedDB<OneElementOf::Auth>::SomethingIsChanged();
}
