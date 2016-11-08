#pragma once
#include <string>
#include <vector>

#include "../../../view/headers/StreamInput.h"
#include "../../other/templates/MyContainer.h"
#include "../../other/headers/ISBNOnePart.h"
//#include "Country.h"

#ifndef AJIOB_UI
#define AJIOB_UI

typedef unsigned long int uli;

#endif

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

//class PublisherBDClass;

namespace OneElementOf
{
	class Publisher;
	class Country;
}

class OneElementOf::Publisher
{
	friend Country;

	std::string cl_name;
	std::string cl_city;
	MyContainer<ISBNOnePart> cl_ISBN_PublisherPart;

	Country* cl_parent;

	void BWrite(const std::string& bInfo, strPos& it);

public:
	Publisher(void* parent = nullptr);
	Publisher(const Publisher& that);
	Publisher(const std::string& bInfo, strPos& it, void* parent);
	~Publisher();

	Publisher& operator=(const Publisher& that);

	std::string BRead() const;

	friend std::ostream& operator<< (std::ostream& s, const Publisher& that);
	friend std::istream& operator>> (std::istream& s, Publisher& that);

	friend Publisher BStringIO::ReadBInfo<Publisher>(const std::string& str, strPos& iterator);
	friend std::string GetBString(const Publisher& info);

	bool WorkWithISBNPublisherPart();

	bool InputNewName();
	//bool InputNewCountry();
	bool InputNewCity();

};

/*
template <>
inline std::string BStringIO::GetBString<OneElementOf::Publisher>(const OneElementOf::Publisher& info)
{
	//return (GetBString(info.length()) + info);
	//return std::string();
	return info.BRead();
}


/*
	DefaultID <AJIOBTypes::PrivelegeType> cl_login;
	std::string cl_password;

public:
	
	DefaultID<AJIOBTypes::PrivelegeType> GetLogin() const;
		
	//void SetLogin(const DefaultID<AJIOBTypes::PrivelegeType>& newLogin);
	void InputNewPrivelege();
	bool InputNewPassword();
	void SetPassword(const std::string& newPassword);
	void ResetPassword();

	void InputAuthFromConsole();

	bool EqualByAll(const Auth& that) const;
	bool EqualByLogin(const Auth& that) const;

	bool operator==(const Auth& that) const;
	/*/