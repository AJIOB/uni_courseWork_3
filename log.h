#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

static const char *logfileWay = "librarylog.log";
static const int strSize = 40;


void AJIOB_ProgramLog(const std::string putToLogFile, const bool isCloseFile = false, const char errorText[] = "Error when open log file");