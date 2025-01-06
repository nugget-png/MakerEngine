#include "MakerEngine.h"

// TODO: Add cross-platform support for DLL entry point

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C" BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD ul_reason_for_call, HINSTANCE hPrevInstance) {
	switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Code to run when the DLL is loaded by a process
		spdlog::info("MakerEngine begin");

        // Allow debug messages to show in debug mode
        #ifdef MAKERENGINE_DEBUG
            spdlog::set_level(spdlog::level::debug);
        #endif

        break;
    case DLL_THREAD_ATTACH:
        // Code to run when a thread is created in a process

        break;
    case DLL_THREAD_DETACH:
        // Code to run when a thread exits cleanly

        break;
    case DLL_PROCESS_DETACH:
        // Code to run when the DLL is unloaded by a process
        spdlog::info("MakerEngine end");
        break;
	}
	return TRUE;
}
#endif
