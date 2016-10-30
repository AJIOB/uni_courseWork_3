#include "MyException.h"

MyException::MyException():exception()
{
	AJIOB_ProgramLog("Error. No error text", true);
}

MyException::MyException(const char* const& errorText):exception(errorText)
{
	AJIOB_ProgramLog("Error. Error text: " + std::string(errorText), true);
}

MyException::MyException(const std::string errorText):exception(errorText.c_str())
{
	AJIOB_ProgramLog("Error. Error text: " + errorText, true);
}
