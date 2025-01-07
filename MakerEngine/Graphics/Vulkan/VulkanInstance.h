#pragma once

#include "MakerEngine.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <cstring>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            class MAKERENGINE_API VulkanInstance {
            public:
                VulkanInstance();
                ~VulkanInstance();

                void create(const std::string& appName, uint32_t appVersion);

            private:

                bool checkValidationLayerSupport();

                void destroy();

                VkInstance instance;
            };
        }
    }
}
