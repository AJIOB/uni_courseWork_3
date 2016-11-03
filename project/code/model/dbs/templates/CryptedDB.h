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
	static void Encrypt(std::string& strToEncrypt, int pos);
	static void Decrypt(std::string& strToDecrypt, int pos);

	
public:
	CryptedDB(const std::string& wayToAuthDBFile, bool isReadOnly = true);
	~CryptedDB();
};



//cpp
template <typename Type>
void CryptedDB<Type>::Encrypt(std::string& strToEncrypt, int pos)
{
	//длины изменяемой строки и пароля соответственно
	auto stlen = strToEncrypt.length();
	auto pwdlen = sizeof password;

	for (auto i = 0; i < stlen; ++i)
	{
		strToEncrypt[i] = strToEncrypt[i] ^ password[(i + pos) % pwdlen];
	}
}

template <typename Type>
void CryptedDB<Type>::Decrypt(std::string& strToDecrypt, int pos)
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

