#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

static const char *logfileWay = "project\\logs\\librarylog.log";
static const int strSize = 40;
static const char errorText[] = "Error when open log file";

namespace AJIOB
{
	void ProgramLog(const std::string putToLogFile, const bool isCloseFile = false);
}

