#pragma once
#include <string>

#include "../../../model/exceptions/AllExceptions.h"
#include "../../other/headers/typedefs.h"
#include "../../../view/headers/view.h"

namespace BStringIO
{
	template <typename InfoType>
	InfoType ReadBInfo(const bString& str, strPos& iterator);

	template <typename InfoType>
	bString MakeBString(const InfoType& info);

	template <typename TypeInfo>
	bool ReadBStringFromDB(const bString& read, TypeInfo& result);
}





//cpp

template <typename TypeInfo>
bool BStringIO::ReadBStringFromDB(const bString& toRead, TypeInfo& result)
{
	TypeInfo buff;
	strPos it = 0;

	try
	{
		buff =  BStringIO::ReadBInfo<TypeInfo>(toRead, it);
	}
	catch(const OutOfBStringLimitException& e)
	{
		OutputError(e.what());
		return false;
	}

	result = buff;
	return true;
}





//default
template <typename InfoType>
InfoType BStringIO::ReadBInfo(const bString& str, strPos& iterator)
{
	if (iterator + sizeof InfoType > str.length())
	{
		throw OutOfBStringLimitException();
	}

	//читаем сам InfoType
	InfoType to_return = *(reinterpret_cast<const InfoType *> (str.c_str() + iterator));
	iterator += sizeof InfoType;

	return to_return;
}

template <typename InfoType>
bString BStringIO::MakeBString(const InfoType& info)
{
	const char* tmp = reinterpret_cast<const char *> (&info);
	return std::string(tmp, sizeof InfoType);
}


//for std::string
template <>
inline std::string BStringIO::ReadBInfo<std::string>(const bString& str, strPos& iterator)
{
	size_t len = ReadBInfo<size_t>(str, iterator);
	if (iterator + len > str.length())
	{
		throw OutOfBStringLimitException();
	}

	//переписываем саму строку
	std::string to_return (str.begin() + iterator, str.begin() + iterator + len);
	iterator += len;

	return to_return;
}

template <>
inline bString BStringIO::MakeBString(const std::string& info)
{
	return (MakeBString(info.length()) + info);
}

/*
//for publisher
template <>
inline OneElementOf::Publisher BStringIO::ReadBInfo<OneElementOf::Publisher>(const bString& str, strPos& iterator)
{
	return OneElementOf::Publisher(str, iterator, nullptr);
}

template <>
inline bString BStringIO::MakeBString<OneElementOf::Publisher>(const OneElementOf::Publisher& info)
{
	//return (MakeBString(info.length()) + info);
	//return std::string();
	return info.BRead();
}*/