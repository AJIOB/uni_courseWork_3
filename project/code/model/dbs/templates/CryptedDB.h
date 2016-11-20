#pragma once

#include "DefaultDB.h"

//Пароль от файла (для расшифровки)
static const char password[] = "Default!@#$%^&*Password123";
//static const char lastChar = 28;

template <typename Type>
class CryptedDB : public DefaultDB<Type>
{
protected:
//public:
	static void Encrypt(std::string& strToEncrypt, const size_t pos);
	static void Decrypt(std::string& strToDecrypt, const size_t pos);

public:
	CryptedDB(const std::string& wayToAuthDBFile, bool isReadOnly = true);
	virtual ~CryptedDB();

	//методы (перегружены)
	void ReadAll() override;
	void WriteAll() override;
};



//cpp
template <typename Type>
void CryptedDB<Type>::Encrypt(std::string& strToEncrypt, const size_t pos)
{
	//длины изменяемой строки и пароля соответственно
	auto stlen = static_cast<long int>(strToEncrypt.length());
	auto pwdlen = sizeof password;

	for (auto i = 0; i < stlen; ++i)
	{
		strToEncrypt[i] = strToEncrypt[i] ^ password[(i + pos) % pwdlen];
	}
}

template <typename Type>
void CryptedDB<Type>::Decrypt(std::string& strToDecrypt, const size_t pos)
{
	//длины изменяемой строки и пароля соответственно
	auto stlen = strToDecrypt.length();
	auto pwdlen = sizeof password;

	for (auto i = 0; i < stlen; ++i)
	{
		strToDecrypt[i] = strToDecrypt[i] ^ password[ (i + pos) % pwdlen];
	}
}

template <typename Type>
CryptedDB<Type>::CryptedDB(const std::string& wayToAuthDBFile, bool isReadOnly = true) : DefaultDB(wayToAuthDBFile, isReadOnly)
{
}

template <typename Type>
CryptedDB<Type>::~CryptedDB()
{
}

template <typename Type>
void CryptedDB<Type>::ReadAll()
{
	if (!FileOpenIn())
	{
		return;
	}

	cl_ourArray.clear();

	strPos it = 0;
	size_t n = BStringIO::ReadBInfo<size_t>(ReadStringFromFile(), it);

	for (size_t i = 0; i < n; ++i)
	{
		auto posInFile = fin.tellg();
		std::string buff = ReadStringFromFile();
		Decrypt(buff, posInFile);
		it = 0;
		cl_ourArray.push_back(Type(buff, it, GetMe()));
	}

	cl_isChanged = false;
}

template <typename Type>
void CryptedDB<Type>::WriteAll()
{
	OutputLog("Сохранение изменений в файле " + cl_fileName);

	FileReset();

	//Пишем количество строк в файле
	WriteStringToFile(BStringIO::MakeBString(cl_ourArray.size()));
	
	for (auto it = cl_ourArray.begin(); it != cl_ourArray.end(); ++it)
	{
		std::string buffstr = it->BRead();
		Encrypt(buffstr, fout.tellp());
		WriteStringToFile(buffstr);
	}

	FileClose();
	cl_isChanged = false;
}
