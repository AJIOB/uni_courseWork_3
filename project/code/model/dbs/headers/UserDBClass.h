#pragma once
#include "../templates/CryptedDB.h"
#include "../../one element of db/headers/User.h"
//#include "../../../view/headers/view.h"

const char UserDBDefaultWay[] = "project\\dbs\\user.db";

class UserDBClass : public CryptedDB<OneElementOf::User>
{
	void Load(bool isReadOnly = true);

public:
	UserDBClass(bool isReadOnly = false);
	~UserDBClass();

	uli GetNewID() const;

	int FindByAuthInfo(const DefaultID& login, const std::string& password) const;
	int FindByAuthInfo(const OneElementOf::User& checkedUser) const;

	/*
	void Save();
	void Unload();

	void Add();
	void Show() const override;
	int Find(const OneElementOf::User& currLP) const;
	void Update() override;
	void Delete() override;
	/*//*
	OneElementOf::User& GetElement(int index);
	const OneElementOf::User& GetElement(int index) const;
	OneElementOf::User& operator[](int index);
	*/
	//void SomethingIsChanged() override;
};
