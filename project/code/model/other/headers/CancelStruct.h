#pragma once

#include <ctime>

#include "../../binary input&output/templates/BStringIO.h"

//время отмены запроса = 1 сутки
const time_t liveTime = 60*60*24;

struct CancelStruct
{
	time_t time;
	bString query;

	CancelStruct();
	CancelStruct(const CancelStruct& that);
	CancelStruct& operator=(const CancelStruct& that);
};