#pragma once

#include "pch.h"

#ifdef Dist
#define MESSAGE_BOX(title, message)
#else
#define MESSAGE_BOX(title, message) MessageBoxW(NULL, (LPCWSTR)L##message, (LPCWSTR)L##title, MB_ICONERROR | MB_YESNO);  
#endif