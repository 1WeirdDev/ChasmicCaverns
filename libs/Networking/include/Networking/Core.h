#pragma once

#if NETWORKING_PLATFORM == WINDOWS
	#define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10
	#define _WIN32_WINNT 0x0A00
	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

	#ifdef NETWORKING_STATIC
		#define NETWORKING_API
	#else
		#ifdef NETWORKING_EXPORTS
				#define NETWORKING_API __declspec(dllexport)
		#else
				#define NETWORKING_API __declspec(dllimport)
		#endif
	#endif
#elif  NETWORKING_PLATFORM == ANDROID
#error NOT FOR ANDROID YET
#define fdeclspec
#else
#error NO PLATFORM FOR NETWORKING LIB
#endif
