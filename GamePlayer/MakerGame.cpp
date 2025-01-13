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

    engine.initialize();
    vulkanInstance.create("Game Player", VK_MAKE_VERSION(1, 0, 0));
    physicalDevice.pickBestDevice(vulkanInstance);
    logicalDevice.create(physicalDevice);
 
    window.create(1280, 720, "Game Player");
    window.runLoop();

    window.destroy();
    engine.shutdown();

    return 0;
}

