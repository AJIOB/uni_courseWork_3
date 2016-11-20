#include "../headers/CancelStruct.h"

CancelStruct::CancelStruct()
{
	time = 0;
	query = "";
}

CancelStruct::CancelStruct(const CancelStruct& that)
{
	(*this) = that;
}

CancelStruct& CancelStruct::operator=(const CancelStruct& that)
{
	time = that.time;
	query = that.query;

	return (*this);
}
