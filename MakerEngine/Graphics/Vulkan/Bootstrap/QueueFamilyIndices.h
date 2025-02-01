#pragma once

#include "MakerEngine.h"
#include "WindowSurface.h"


#include <optional>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                struct QueueFamilyIndices {
                    std::optional<uint32_t> graphicsFamily;
                    std::optional<uint32_t> presentFamily;

                    bool isComplete() {
                        return graphicsFamily.has_value() && presentFamily.has_value();
                    }
                };

                MAKERENGINE_API QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, const std::optional<WindowSurface>& surface);
            }
        }
    }
}
