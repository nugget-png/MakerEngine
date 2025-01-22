#pragma once

#include "MakerEngine.h"

#include "VulkanInstance.h"
#include "QueueFamilyIndices.h"

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <vulkan/vulkan.h>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                class MAKERENGINE_API PhysicalDevice {
                public:
                    PhysicalDevice();
                    ~PhysicalDevice();

                    void pickBestDevice(const VulkanInstance& instance);

                    const VkPhysicalDevice& getHandle() const;

                private:
                    std::vector<VkPhysicalDevice> enumeratePhysicalDevices(const VulkanInstance& instance);

                    VkPhysicalDeviceProperties getDeviceProperties(const VkPhysicalDevice& physicalDevice) const;
                    VkPhysicalDeviceFeatures getDeviceFeatures(const VkPhysicalDevice& physicalDevice) const;
                    VkPhysicalDeviceMemoryProperties getDeviceMemoryProperties(const VkPhysicalDevice& physicalDevice) const;

                    int rateDeviceSuitability(const VkPhysicalDevice& physicalDevice) const;

                    VkPhysicalDevice physicalDevice;
                };
            }
        }
    }
}
