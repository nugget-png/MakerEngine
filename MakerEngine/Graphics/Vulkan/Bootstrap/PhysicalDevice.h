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

                    VkPhysicalDevice getHandle() const;

                private:
                    std::vector<VkPhysicalDevice> enumeratePhysicalDevices(const VulkanInstance& instance);

                    VkPhysicalDeviceProperties getDeviceProperties(VkPhysicalDevice physicalDevice) const;
                    VkPhysicalDeviceFeatures getDeviceFeatures(VkPhysicalDevice physicalDevice) const;
                    VkPhysicalDeviceMemoryProperties getDeviceMemoryProperties(VkPhysicalDevice physicalDevice) const;

                    int rateDeviceSuitability(VkPhysicalDevice physicalDevice) const;

                    VkPhysicalDevice physicalDevice;
                };
            }
        }
    }
}
