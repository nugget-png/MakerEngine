#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <set>
#include "QueueFamilyIndices.h"
#include "PhysicalDevice.h"
#include "WindowSurface.h"
#include "MakerEngine.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                class MAKERENGINE_API LogicalDevice {
                public:
                    LogicalDevice();
                    ~LogicalDevice();

                    void create(const PhysicalDevice& physicalDevice, const std::optional<WindowSurface>& windowSurface);

                    VkDevice getHandle() const;

                    VkQueue getGraphicsQueue() const;
                    VkQueue getPresentationQueue() const;

                private:
                    VkDeviceQueueCreateInfo LogicalDevice::createQueue(
                        const uint32_t queueFamilyIndex,
                        const uint32_t queueCount,
                        float queuePriority
                    ) const;

                    bool isExtensionSupported(VkPhysicalDevice physicalDevice, const char* extensionName) const;

                    VkDevice device;
                    VkQueue graphicsQueue;
                    VkQueue presentQueue;
                };
            }
        }
    }
}
