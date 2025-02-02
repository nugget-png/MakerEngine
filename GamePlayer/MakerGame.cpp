#include <iostream>
#include <MakerEngine.h>
#include <Application/Window.h>
#include <Graphics/Vulkan/Bootstrap/VulkanInstance.h>
#include <Graphics/Vulkan/Bootstrap/PhysicalDevice.h>
#include <Graphics/Vulkan/Bootstrap/LogicalDevice.h>
#include <Scripting/Lua/LuaStateManager.h>

using namespace MakerEngine;
using namespace MakerEngine::Graphics;

int main() {
    Engine engine;
    Application::Window window;
    Vulkan::Bootstrap::VulkanInstance vulkanInstance;
    Vulkan::Bootstrap::PhysicalDevice physicalDevice;
    Vulkan::Bootstrap::LogicalDevice logicalDevice;
    Vulkan::Bootstrap::WindowSurface windowSurface;

    Scripting::Lua::LuaStateManager lua;

    try {
        engine.initialize();
        vulkanInstance.create("Game Player", VK_MAKE_VERSION(1, 0, 0));
        physicalDevice.pickBestDevice(vulkanInstance);

        window.create(1280, 720, "Game Player");
        windowSurface.create(vulkanInstance, window);
        logicalDevice.create(physicalDevice, windowSurface);
        lua.executeFile("script.lua");

        window.runLoop();

        windowSurface.destroy(vulkanInstance);
        engine.shutdown();
    }
    catch (const std::exception& e) {
        // Still cleanup after a critical exception is caught
        std::cerr << "Exception caught: " << e.what() << std::endl;
        windowSurface.destroy(vulkanInstance);
        engine.shutdown();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

