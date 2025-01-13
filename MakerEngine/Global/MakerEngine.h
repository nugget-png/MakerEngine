#pragma once

// Description: Global definitions for the engine

#include <string>
#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

// Engine details
#define ENGINE_NAME "Maker Engine"
#define ENGINE_VERSION VK_MAKE_VERSION(0, 1, 0)
#define VULKAN_API_VERSION VK_MAKE_VERSION(1, 3, 296)

#ifdef _WIN32
	#define PLATFORM_WINDOWS
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__APPLE__)
	#define PLATFORM_MACOS
#endif

#ifdef _DEBUG
    #define MAKERENGINE_DEBUG
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
