#pragma once
#include <string>

#include "../../../model/exceptions/AllExceptions.h"

typedef unsigned int strPos;

class BStringIO
{
public:
	template <typename InfoType>
	static InfoType ReadBInfo(const std::string& str, strPos& iterator);

	template <typename InfoType>
	static std::string GetBString(InfoType info);
};


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
std::string BStringIO::GetBString(InfoType info)
{
	char* tmp = reinterpret_cast<char *> (&info);
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
inline std::string BStringIO::GetBString(std::string info)
{
	return (GetBString(info.length()) + info);
}