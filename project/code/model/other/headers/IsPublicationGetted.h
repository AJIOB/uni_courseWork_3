#pragma once
#include "../templates/DefaultID.h"
//#include "../../enums/PrivelegeType.h"

struct IsPublicationGetted
{
	bool cl_isGetted;
	DefaultID<AJIOBTypes::PrivelegeType::PrivelegeType> cl_whoIsGet;
};
