#pragma once

#include <ctime>

#include "../../binary input&output/templates/BStringIO.h"


struct CancelStruct
{
	time_t time;
	bString query;

	CancelStruct();
	CancelStruct(const CancelStruct& that);
	CancelStruct& operator=(const CancelStruct& that);
};
