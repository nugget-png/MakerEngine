#include <iostream>
#include <MakerEngine.h>
#include <Application/Window.h>
#include <Graphics/Vulkan/Bootstrap/VulkanInstance.h>
#include <Graphics/Vulkan/Bootstrap/PhysicalDevice.h>
#include <Graphics/Vulkan/Bootstrap/LogicalDevice.h>

using namespace MakerEngine;
using namespace MakerEngine::Graphics;

int main() {
    Engine engine;
    Application::Window window;
    Vulkan::Bootstrap::VulkanInstance vulkanInstance;
    Vulkan::Bootstrap::PhysicalDevice physicalDevice;
    Vulkan::Bootstrap::LogicalDevice logicalDevice;
    Vulkan::Bootstrap::WindowSurface windowSurface;

    engine.initialize();
    vulkanInstance.create("Game Player", VK_MAKE_VERSION(1, 0, 0));
    physicalDevice.pickBestDevice(vulkanInstance);

    window.create(1280, 720, "Game Player");
    windowSurface.create(vulkanInstance, window);
    logicalDevice.create(physicalDevice, windowSurface);
    window.runLoop();

    windowSurface.destroy(vulkanInstance);
    engine.shutdown();

    return 0;
}

