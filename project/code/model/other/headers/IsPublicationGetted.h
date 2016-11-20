#pragma once
#include <iomanip>

#include "../headers/DefaultID.h"

class IsPublicationGetted
{
	bool cl_isArcheved;
	bool cl_isGetted;
	DefaultID cl_whoIsGet;

	void BWrite(const bString& bInfo, strPos& it);
public:
	IsPublicationGetted();
	IsPublicationGetted(const IsPublicationGetted& that);
	IsPublicationGetted(const bString& bInfo, strPos& it);
	~IsPublicationGetted();

	IsPublicationGetted& operator=(const IsPublicationGetted& that);

	std::string BRead() const;

	bool GetIsArchieved() const;
	bool GetIsGetted() const;
	DefaultID GetWhoIsGet() const; 

	bool Archieve();

	bool GetTo(const DefaultID& person);

	//TODO
	bool UpdateMe();

	friend std::ostream& operator<<(std::ostream& s, const IsPublicationGetted& elem);
};
