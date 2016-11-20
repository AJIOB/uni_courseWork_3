#include "../headers/AuthDBClass.h"

AuthDBClass::AuthDBClass(bool isReadOnly)
	: CryptedDB<OneElementOf::Auth>(LoginDBDefaultWay, isReadOnly)
{
	//cl_readOnly = isReadOnly;
	Load(isReadOnly);
}

AuthDBClass::~AuthDBClass()
{
	Unload();
}

void AuthDBClass::Load(bool isReadOnly)
{
	cl_readOnly = isReadOnly;
	ReadAll();
}

bool AuthDBClass::UpdateElement(OneElementOf::Auth& elem)
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

/*
void AuthDBClass::Add()
{
	CryptedDB<OneElementOf::Auth>::Add();
}

void AuthDBClass::Show() const
{
	CryptedDB<OneElementOf::Auth>::Show();
}*/

int AuthDBClass::Find(const OneElementOf::Auth& currLP) const
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
/*
void AuthDBClass::Update()
{
	CryptedDB<OneElementOf::Auth>::Update();
}

void AuthDBClass::Delete()
{
	CryptedDB<OneElementOf::Auth>::Delete();
}*/

OneElementOf::Auth& AuthDBClass::GetElement(int index)
{
	return cl_ourArray[index];
}

const OneElementOf::Auth& AuthDBClass::GetElement(int index) const
{
	return cl_ourArray[index];
}

OneElementOf::Auth& AuthDBClass::operator[](int index)
{
	return GetElement(index);
}
/*
void AuthDBClass::SomethingIsChanged()
{
	CryptedDB<OneElementOf::Auth>::SomethingIsChanged();
}
*/