#include "PhysicalDevice.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                PhysicalDevice::PhysicalDevice()
                    : physicalDevice(VK_NULL_HANDLE)
                {
                    // Empty constructor
                }

                std::vector<VkPhysicalDevice> PhysicalDevice::enumeratePhysicalDevices(const VulkanInstance& instance) {
                    uint32_t deviceCount = 0;

                    vkEnumeratePhysicalDevices(instance.getHandle(), &deviceCount, nullptr);

                    // If no devices are found, no point in going further
                    if (deviceCount == 0) {
                        spdlog::critical("No Vulkan-compatible devices found!");
                        throw std::runtime_error("No Vulkan-compatible devices found!");
                    }

                    std::vector<VkPhysicalDevice> devices(deviceCount);
                    vkEnumeratePhysicalDevices(instance.getHandle(), &deviceCount, devices.data());
                    spdlog::debug("Found {} Vulkan-compatible devices.", deviceCount);

                    // Return all available devices
                    return devices;
                }

                void PhysicalDevice::pickBestDevice(const VulkanInstance& instance) {
                    std::unordered_map<VkPhysicalDevice, int> candidates;

                    std::vector<VkPhysicalDevice> devices = enumeratePhysicalDevices(instance);

                    for (const auto& device : devices) {
                        int score = rateDeviceSuitability(device);
                        candidates.emplace(device, score);
                    }

                    VkPhysicalDevice bestDevice = VK_NULL_HANDLE;
                    int highestScore = -1;

                    for (const auto& candidate : candidates) {
                        if (candidate.second > highestScore) {
                            bestDevice = candidate.first;
                            highestScore = candidate.second;
                        }
                    }

                    // Set the physical device to the best device

                    VkPhysicalDeviceProperties properties = getDeviceProperties(bestDevice);
                    spdlog::debug("Using a suitable device: {}", properties.deviceName);

                    physicalDevice = bestDevice;
                }

                VkPhysicalDeviceFeatures PhysicalDevice::getDeviceFeatures(const VkPhysicalDevice& physicalDevice) const {
                    VkPhysicalDeviceFeatures deviceFeatures;
                    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
                    return deviceFeatures;
                }

                VkPhysicalDeviceProperties PhysicalDevice::getDeviceProperties(const VkPhysicalDevice& physicalDevice) const {
                    VkPhysicalDeviceProperties deviceProperties;
                    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
                    return deviceProperties;
                }

                VkPhysicalDeviceMemoryProperties PhysicalDevice::getDeviceMemoryProperties(const VkPhysicalDevice& physicalDevice) const {
                    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
                    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemoryProperties);
                    return deviceMemoryProperties;
                }

                int PhysicalDevice::rateDeviceSuitability(const VkPhysicalDevice& physicalDevice) const {
                    VkPhysicalDeviceProperties deviceProperties = getDeviceProperties(physicalDevice);
                    VkPhysicalDeviceFeatures deviceFeatures = getDeviceFeatures(physicalDevice);

                    int score = 0;

                    spdlog::debug("Evaluating device: {}", deviceProperties.deviceName);

                    // Geometry shaders are essential
                    if (!deviceFeatures.geometryShader) {
                        spdlog::debug("Device does not support geometry shader. Device is not suitable.");
                        return 0;
                    }


                    // Ensure the device has the available queue families
                    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, std::nullopt);
                    if (!indices.graphicsFamily.has_value()) {
                        return 0;
                    }

                    spdlog::debug("Device supports geometry shader.");

                    // Discrete GPUs have a significant performance advantage
                    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                        spdlog::debug("Device is a discrete GPU.");
                        score += 2000;
                    }

                    // Integrated GPUs are still acceptable
                    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
                        spdlog::debug("Device is a integrated GPU.");
                        score += 1000;
                    }

                    // Check for multiple viewport support
                    if (deviceFeatures.multiViewport) {
                        spdlog::debug("Device supports multiple viewports.");
                        score += 2000;
                    }

                    // Check for tesselation shader support
                    if (deviceFeatures.tessellationShader) {
                        spdlog::debug("Device supports tesselation shader.");
                        score += 1000;
                    }

                    // Add score based on limits
                    score += deviceProperties.limits.maxViewports;
                    score += deviceProperties.limits.maxImageDimension1D;
                    score += deviceProperties.limits.maxImageDimension2D;
                    score += deviceProperties.limits.maxImageDimension3D;
                    score += deviceProperties.limits.maxCullDistances;

                    // Log the results
                    spdlog::debug("Device limits:");
                    spdlog::debug("  Max Viewports: {}", deviceProperties.limits.maxViewports);
                    spdlog::debug("  Max Image Dimension 1D: {}", deviceProperties.limits.maxImageDimension1D);
                    spdlog::debug("  Max Image Dimension 2D: {}", deviceProperties.limits.maxImageDimension2D);
                    spdlog::debug("  Max Image Dimension 3D: {}", deviceProperties.limits.maxImageDimension3D);
                    spdlog::debug("  Max Cull Distances: {}", deviceProperties.limits.maxCullDistances);

                    spdlog::debug("Device final suitability score: {}", score);

                    return score;
                }

                const VkPhysicalDevice& PhysicalDevice::getHandle() const {
                    return physicalDevice;
                }

                PhysicalDevice::~PhysicalDevice() {
                    // Empty destructor
                }
            }
        }
    }
}
