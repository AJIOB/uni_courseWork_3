#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "../../external/headers/ExternalLib.h"
#include "log.h"

void OutputInfo(const std::string&);
void OutputWarning(const std::string&);
void OutputError(const std::string&);
void OutputLog(const std::string&, const bool isCloseFile = false);

std::string OutputEnum(const std::vector<std::string>& texts, const int& enumToShow);