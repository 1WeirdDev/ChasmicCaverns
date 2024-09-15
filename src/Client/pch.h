#pragma once

#include <iostream>
#include <fstream>

#include <functional>
#include <algorithm>

#include <chrono>
#include <string>

#include <array>
#include <vector>

#include <cstdint>

#if Platform == Windows
    extern "C" {
    #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
    #define NOMINMAX             // Prevents min/max macros from being defined

    #ifndef UNICODE
    #define UNICODE
    #define UNICODE_WAS_UNDEFINED
    #endif

    #include <Windows.h>
    #undef APIENTRY  // Undefine conflicting macro

    #ifdef UNICODE_WAS_UNDEFINED
    #undef UNICODE
    #endif

    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
    }

#else
#error invalid platform
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef USE_SPDLOG

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#endif