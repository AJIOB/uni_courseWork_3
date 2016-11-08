#pragma once

#include <string>
#include <iostream>
#include <windows.h>

#include "../../view/headers/StreamInput.h"
#include "../../model/exceptions/AllExceptions.h"

std::string getpass(const char *prompt, bool show_asterisk=true);


BOOL CtrlHandler( DWORD fdwCtrlType );