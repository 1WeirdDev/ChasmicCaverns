#pragma once

#include "pch.h"

#ifdef DIST
#define MESSAGE_BOX(title, message)
#else
#define MESSAGE_BOX(title, message) MessageBoxW(NULL, L##message, L##title, MB_ICONERROR | MB_YESNO);  
#endif

#define GAME_NAME "CasmicCavernsBeta"