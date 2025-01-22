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
                    VkResult resultFirst = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
                    if (resultFirst != VK_SUCCESS) {
                        spdlog::critical("Failed to query surface capabilities!");
                        throw std::runtime_error("Failed to query surface cababilities!");
                    }

                    // Query the format count
                    if (formatCount != 0) {
                        details.formats.resize(formatCount);
                        VkResult resultSecond =
                            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());

                        if (resultSecond != VK_SUCCESS) {
                            spdlog::critical("Failed to query surface format count!");
                            throw std::runtime_error("Failed to query surface format count!");
                        }
                    }

                    // Query the present mode count
                    uint32_t presentModeCount;

                    VkResult resultThird =
                        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

                    if (resultThird != VK_SUCCESS) {
                        spdlog::critical("Failed to query surface present mode count!");
                        throw std::runtime_error("Failed to query surface present mode count!");
                    }

                    if (presentModeCount != 0) {
                        details.presentModes.resize(presentModeCount);
                        VkResult resultLast =
                            vkGetPhysicalDeviceSurfacePresentModesKHR(
                                physicalDevice, surface, &presentModeCount, details.presentModes.data()
                            );

                        if (resultLast != VK_SUCCESS) {
                            spdlog::critical("Failed to query surface present mode count!");
                            throw std::runtime_error("Failed to query surface present mode count!");
                        }
                    }

                    // Return the details after they are ready
                    return details;
                }
            }
        }
    }
}
