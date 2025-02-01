#include "LogicalDevice.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                LogicalDevice::LogicalDevice()
                    : device(VK_NULL_HANDLE), graphicsQueue(VK_NULL_HANDLE), presentQueue(VK_NULL_HANDLE)
                {

                }

                void LogicalDevice::create(const PhysicalDevice& physicalDevice, const std::optional<WindowSurface>& windowSurface) {
                    // Specify the queues to be created
                    QueueFamilyIndices indices = findQueueFamilies(physicalDevice.getHandle(), windowSurface);

                    // Create a vector to hold all of the queue create infos
                    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

                    // // Add graphics queue with priority 1.0f
                    queueCreateInfos.emplace_back(createQueue(indices.graphicsFamily.value(), 2, 1.0f));

                    // Specify the device features to be enabled
                    VkPhysicalDeviceFeatures deviceFeatures{};

                    // Fill in the main device create info structure
                    VkDeviceCreateInfo createInfo{};
                    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pQueueCreateInfos = queueCreateInfos.data();
                    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
                    createInfo.pEnabledFeatures = &deviceFeatures;

                    // Specify device extensions to use
                    std::vector<const char*> extensions = {
                        VK_KHR_SWAPCHAIN_EXTENSION_NAME
                    };

                    // Ensure all requested extensions are available 
                    for (const auto& extension : extensions) {
                        if (!isExtensionSupported(physicalDevice.getHandle(), extension)) {
                            spdlog::critical("A requested device extension is unavailable!");
                            throw std::runtime_error("A requested device extension is unavailable!");
                        }
                    }

                    // Enable the extensions
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
                    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
                }

                const VkDevice& LogicalDevice::getHandle() const {
                    return device;
                }

                const VkQueue& LogicalDevice::getGraphicsQueue() const {
                    return graphicsQueue;
                }

                const VkQueue& LogicalDevice::getPresentationQueue() const {
                    return presentQueue;
                }

                const VkDeviceQueueCreateInfo LogicalDevice::createQueue(
                    const uint32_t queueFamilyIndex,
                    const uint32_t queueCount,
                    float queuePriority
                ) const

                {
                    VkDeviceQueueCreateInfo queueCreateInfo{};
                    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
                    queueCreateInfo.queueCount = queueCount;
                    queueCreateInfo.pQueuePriorities = &queuePriority;
                    return queueCreateInfo;
                }

                bool LogicalDevice::isExtensionSupported(VkPhysicalDevice physicalDevice, const char* extensionName) const {
                    uint32_t extensionCount;

                    VkResult resultFirst =
                        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

                    if (resultFirst != VK_SUCCESS) {
                        spdlog::critical("Failed to enumerate logical device extension properties!");
                        throw std::runtime_error("Failed to enumerate logical device extension properties!");
                    }

                    std::vector<VkExtensionProperties> supportedExtensions(extensionCount);

                    VkResult resultSecond =
                        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, supportedExtensions.data());

                    if (resultSecond != VK_SUCCESS) {
                        spdlog::critical("Failed to enumerate logical device extension properties!");
                        throw std::runtime_error("Failed to enumerate logical device extension properties!");
                    }

                    for (const auto& extension : supportedExtensions) {
                        if (std::strcmp(extension.extensionName, extensionName) == 0) {
                            return true;
                        }
                    }
                    return false;
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
