#include "MakerEngine.h"

namespace MakerEngine {
	std::string currentPlatform() {
		std::string platform;

		#ifdef PLATFORM_WINDOWS
			platform = "Windows";
		#elif PLATFORM_LINUX
			platform = "Linux";
		#elif PLATFORM_MACOS
			platform = "macOS";
		#else
			// In case of an error, return "Unknown"
			platform = "Unknown";
		#endif

		return platform;
	}

	MakerEngine::MakerEngine() {

	}

	MakerEngine::~MakerEngine() {

	}

	void MakerEngine::initialize() {
		spdlog::info("MakerEngine initializing");
		spdlog::info("Running on ", currentPlatform(), " platform");
	}

	void MakerEngine::shutdown() {
		spdlog::info("MakerEngine shutting down");
	}
}