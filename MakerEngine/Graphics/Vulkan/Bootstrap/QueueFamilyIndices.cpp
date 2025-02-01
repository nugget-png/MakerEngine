#include "QueueFamilyIndices.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                MAKERENGINE_API QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, const std::optional<WindowSurface>& surface) {
                    QueueFamilyIndices indices;
                    uint32_t queueFamilyCount;

                    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
                    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
                    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

                    int i = 0;

                    for (const auto& queueFamily : queueFamilies) {
                        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                            indices.graphicsFamily = i;

                            if (surface.has_value()) {
                                VkBool32 presentSupport = false;
                                VkResult result =
                                    vkGetPhysicalDeviceSurfaceSupportKHR(
                                        physicalDevice, i, surface.value().getHandle(), &presentSupport
                                    );

                                if (result != VK_SUCCESS) {
                                    spdlog::critical("Failed to query surface support!");
                                    throw std::runtime_error("Failed to query surface support!");
                                }

                                if (presentSupport) {
                                    indices.presentFamily = i;
                                }
                            }
                        }

                        i++;
                    }

                    return indices;
                }
            }
        }
    }
}
