#pragma once

#include "MakerEngine.h"

#include <optional>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                struct MAKERENGINE_API QueueFamilyIndices {
                    std::optional<uint32_t> graphicsFamily;
                    // Add more necessary queue family indices here

                    bool isComplete() {
                        return graphicsFamily.has_value();
                    }
                };

                MAKERENGINE_API QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice) {
                    QueueFamilyIndices indices;
                    uint32_t queueFamilyCount;

                    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
                    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
                    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

                    int i = 0;
                    for (const auto& queueFamily : queueFamilies) {
                        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                            indices.graphicsFamily = i;
                        }

                        i++;
                    }

                    return indices;
                }
            }
        }
    }
}
