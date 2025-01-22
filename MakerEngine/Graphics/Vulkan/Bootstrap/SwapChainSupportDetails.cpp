#include "SwapChainSupportDetails.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                MAKERENGINE_API SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface) {
                    SwapChainSupportDetails details;

                    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

                    // Query the surface capabiliies
                    uint32_t formatCount;
                    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

                    // Query the format count
                    if (formatCount != 0) {
                        details.formats.resize(formatCount);
                        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
                    }

                    // Query the present mode count
                    uint32_t presentModeCount;
                    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

                    if (presentModeCount != 0) {
                        details.presentModes.resize(presentModeCount);
                        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
                    }

                    // Return the details after they are ready
                    return details;
                }
            }
        }
    }
}
