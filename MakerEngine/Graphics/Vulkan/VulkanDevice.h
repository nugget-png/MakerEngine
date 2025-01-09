#pragma once

#include "MakerEngine.h"

#include <vulkan/vulkan.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "VulkanInstance.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            class MAKERENGINE_API VulkanDevice {
            public:
                VulkanDevice();
                ~VulkanDevice();

                void pickPhysicalDevice(VulkanInstance& vulkan);

                const VkPhysicalDevice& getPhysicalDevice() const;
                
            private:
                int rateDeviceSuitability(VkPhysicalDevice device);

                VkPhysicalDevice physicalDevice;

            };
        }
    }
}
