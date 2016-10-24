#include "authClass.h"

void AuthClass::ReadAllFile()
{
}

AuthClass::AuthClass(): loginDB(wayToLoginDB)
{
	ReadAllFile();
}

AuthClass::~AuthClass()
{
	//DBArray.clear();
}

int AuthClass::run()
{
	return 0;
}
