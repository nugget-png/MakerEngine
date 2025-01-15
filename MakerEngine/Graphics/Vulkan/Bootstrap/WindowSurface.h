#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../Application/Window.h"
#include "VulkanInstance.h"
#include "MakerEngine.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                class MAKERENGINE_API WindowSurface {
                public:
                    WindowSurface();

                    void create(const VulkanInstance& instance, const Application::Window& window);
                    void destroy(const VulkanInstance& instance);

                private:
                    VkSurfaceKHR surface;
                };
            }
        }
    }
}
