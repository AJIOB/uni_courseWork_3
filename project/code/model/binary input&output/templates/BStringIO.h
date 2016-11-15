#pragma once
#include <string>

#include "../../../model/exceptions/AllExceptions.h"
#include "../../one element of db/headers/Publisher.h"

#ifndef AJIOB_BStringIO_header
#define AJIOB_BStringIO_header

#ifndef AJIOB_STRPOS
#define AJIOB_STRPOS
typedef unsigned int strPos;
#endif

namespace BStringIO
{
	template <typename InfoType>
	InfoType ReadBInfo(const std::string& str, strPos& iterator);

	template <typename InfoType>
	std::string GetBString(const InfoType& info);
}

#endif


//default
template <typename InfoType>
InfoType BStringIO::ReadBInfo(const std::string& str, strPos& iterator)
{
	if (iterator + sizeof InfoType > str.length())
	{
		throw MyException("Ошибка чтения из бинарной строки. Выход за пределы.");
	}

	//читаем сам InfoType
	InfoType to_return = *(reinterpret_cast<const InfoType *> (str.c_str() + iterator));
	iterator += sizeof InfoType;

	return to_return;
}

template <typename InfoType>
std::string BStringIO::GetBString(const InfoType& info)
{
	const char* tmp = reinterpret_cast<const char *> (&info);
	return std::string(tmp, sizeof InfoType);
}


//for std::string
template <>
inline std::string BStringIO::ReadBInfo<std::string>(const std::string& str, strPos& iterator)
{
	size_t len = ReadBInfo<size_t>(str, iterator);
	if (iterator + len > str.length())
	{
		throw MyException("Ошибка чтения из бинарной строки. Выход за пределы.");
	}

	//переписываем саму строку
	std::string to_return (str.begin() + iterator, str.begin() + iterator + len);
	iterator += len;

	return to_return;
}

template <>
inline std::string BStringIO::GetBString(const std::string& info)
{
	return (GetBString(info.length()) + info);
}


//for publisher
template <>
inline OneElementOf::Publisher BStringIO::ReadBInfo<OneElementOf::Publisher>(const std::string& str, strPos& iterator)
{
	return OneElementOf::Publisher(str, iterator, nullptr);

	/*
	size_t len = ReadBInfo<size_t>(str, iterator);
	if (iterator + len > str.length())
	{
		throw MyException("Ошибка чтения из бинарной строки. Выход за пределы.");
	}

	//переписываем саму строку
	std::string to_return (str.begin() + iterator, str.begin() + iterator + len);
	iterator += len;

	return to_return;*/
}

template <>
inline std::string BStringIO::GetBString<OneElementOf::Publisher>(const OneElementOf::Publisher& info)
{
	//return (GetBString(info.length()) + info);
	//return std::string();
	return info.BRead();
}