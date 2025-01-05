#pragma once

// Description: Global definitions for the engine

#include <string>

#ifdef _WIN32
	#define PLATFORM_WINDOWS
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__APPLE__)
	#define PLATFORM_MACOS
#endif

#ifdef PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#ifdef MAKERENGINE_EXPORTS
		#define MAKERENGINE_API __declspec(dllexport)
	#else
		#define MAKERENGINE_API __declspec(dllimport)
	#endif
#elif PLATFORM_LINUX || PLATFORM_MACOS // Linux and macOS both use __attribute__((visibility("default")))
	#ifdef MAKERENGINE_EXPORTS
		#define MAKERENGINE_API __attribute__((visibility("default")))
	#else
		#define MAKERENGINE_API
	#endif
#endif

namespace MakerEngine {
	std::string& MAKERENGINE_API currentPlatform();
}