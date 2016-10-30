#include "MyLibrary.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	programBegin();

	int errorCode = defaultFunction();
	
	programEnd();
	return errorCode;
}