#include <iostream>
#include <MakerEngine.h>
#include <Application/Window.h>
#include <Graphics/Vulkan/VulkanInstance.h>

using namespace MakerEngine;

int main() {
    Engine engine;
    Application::Window window;
    Graphics::Vulkan::VulkanInstance vulkanInstance;

    engine.initialize();
    vulkanInstance.create("Game Player", VK_MAKE_VERSION(1, 0, 0));

 
    window.create(1280, 720, "Game Player");
    window.runLoop();

    window.destroy();
    engine.shutdown();

    // No need to clean up VulkanInstance, its done automatically in its destructor

    return 0;
}

