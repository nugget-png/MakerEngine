#include "LogicalDevice.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                LogicalDevice::LogicalDevice()
                    : device(VK_NULL_HANDLE), graphicsQueue(VK_NULL_HANDLE)
                {

                }

                void LogicalDevice::create(PhysicalDevice& physicalDevice) {
                    // Specify the queues to be created
                    QueueFamilyIndices indices = findQueueFamilies(physicalDevice.getHandle());

                    VkDeviceQueueCreateInfo queueCreateInfo{};
                    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
                    queueCreateInfo.queueCount = 1;

                    float queuePriority = 1.0f;
                    queueCreateInfo.pQueuePriorities = &queuePriority;

                    // Specify the device features to be enabled
                    VkPhysicalDeviceFeatures deviceFeatures{};

                    // Fill in the main device create info structure
                    VkDeviceCreateInfo createInfo{};
                    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pQueueCreateInfos = &queueCreateInfo;
                    createInfo.queueCreateInfoCount = 1;
                    createInfo.pEnabledFeatures = &deviceFeatures;

                    // Specify device extensions to use
                    std::vector<const char*> extensions = {
                        VK_KHR_SWAPCHAIN_EXTENSION_NAME
                    };

                    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
                    createInfo.ppEnabledExtensionNames = extensions.data();

                    spdlog::debug("Enabled extension names for logical device: ");
                    for (uint32_t i = 0; i < createInfo.enabledExtensionCount; ++i) {
                        spdlog::debug(" {}", createInfo.ppEnabledExtensionNames[i]);
                    }

                    // Create the logical device
                    VkResult result = vkCreateDevice(physicalDevice.getHandle(), &createInfo, nullptr, &device);
                    if (result != VK_SUCCESS) {
                        spdlog::critical("Failed to create logical device!");
                        throw std::runtime_error("Failed to create logical device!");
                    }

                    spdlog::debug("Successfully created logical device");

                    // Get the device queues
                    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
                }

                const VkDevice& LogicalDevice::getHandle() const {
                    return device;
                }

                const VkQueue& LogicalDevice::getGraphicsQueue() const {
                    return graphicsQueue;
                }

                LogicalDevice::~LogicalDevice() {
                    if (device) {
                        vkDestroyDevice(device, nullptr);
                    }
                }
            }
        }
    }
}
