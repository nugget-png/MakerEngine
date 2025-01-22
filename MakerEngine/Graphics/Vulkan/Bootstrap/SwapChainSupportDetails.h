#pragma once

#include "MakerEngine.h"

#include <vulkan/vulkan.h>
#include <vector>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                struct SwapChainSupportDetails {
                    VkSurfaceCapabilitiesKHR capabilities;
                    std::vector<VkSurfaceFormatKHR> formats;
                    std::vector<VkPresentModeKHR> presentModes;
                };

                MAKERENGINE_API SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);
            }
        }
    }
}
