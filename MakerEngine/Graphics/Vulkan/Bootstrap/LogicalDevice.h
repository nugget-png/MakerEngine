#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include "QueueFamilyIndices.h"
#include "PhysicalDevice.h"
#include "MakerEngine.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                class MAKERENGINE_API LogicalDevice {
                public:
                    LogicalDevice();
                    ~LogicalDevice();

                    void create(PhysicalDevice& physicalDevice);

                    const VkDevice& getHandle() const;

                    const VkQueue& getGraphicsQueue() const;



                private:
                    VkDevice device;
                    VkQueue graphicsQueue;
                };
            }
        }
    }
}
