#pragma once

// Description: Global definitions for the engine

#include <string>
#include <spdlog/spdlog.h>

#ifdef _WIN32
	#define PLATFORM_WINDOWS
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__APPLE__)
	#define PLATFORM_MACOS
#endif

#ifdef PLATFORM_WINDOWS
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
	MAKERENGINE_API std::string currentPlatform();

	class MAKERENGINE_API Engine {
	public:
		Engine();
		~Engine();

		void initialize();
		void shutdown();
	private:
		// No private members for now
	};
}