#pragma once

#include "MakerEngine.h"

#include <optional>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                struct QueueFamilyIndices {
                    std::optional<uint32_t> graphicsFamily;
                    // Add more necessary queue family indices here

                    bool isComplete() {
                        return graphicsFamily.has_value();
                    }
                };

                MAKERENGINE_API QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
            }
        }
    }
}
