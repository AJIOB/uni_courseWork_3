#pragma once
#include "../templates/CryptedDB.h"
#include "../../one element of db/headers/Auth.h"
#include "../../../view/headers/view.h"

const char LoginDBDefaultWay[] = "project\\dbs\\auth.db";

class LoginDBClass : private CryptedDB<OneElementOf::Auth>
{
	void Load(bool isReadOnly = true);

	bool UpdateElement(OneElementOf::Auth& elem) override;

public:
	LoginDBClass(bool isReadOnly = false);
	~LoginDBClass();
	
	void Save();
	void Unload();

	void Add();
	void Show() const override;
	int Find(const OneElementOf::Auth& currLP) const;
	void Update() override;
	void Delete() override;

	OneElementOf::Auth& GetElement(int index);
	const OneElementOf::Auth& GetElement(int index) const;
	OneElementOf::Auth& operator[](int index);

	void SomethingIsChanged() override;
};
