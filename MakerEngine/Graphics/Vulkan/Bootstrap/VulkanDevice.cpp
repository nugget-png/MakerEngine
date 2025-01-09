#include "VulkanDevice.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                VulkanDevice::VulkanDevice()
                    : physicalDevice(VK_NULL_HANDLE)
                {

                }

                void VulkanDevice::pickPhysicalDevice(VulkanInstance& vulkan) {
                    uint32_t deviceCount = 0;

                    vkEnumeratePhysicalDevices(vulkan.getVkInstance(), &deviceCount, nullptr);
                    std::vector<VkPhysicalDevice> devices;

                    // If there are no devices, no point in going further
                    if (deviceCount == 0) {
                        spdlog::critical("Failed to find GPUs with Vulkan support!");
                        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
                    }

                    vkEnumeratePhysicalDevices(vulkan.getVkInstance(), &deviceCount, devices.data());

                    // Pick the best GPU to use
                    std::unordered_map<VkPhysicalDevice, int> candidates;

                    for (const auto& device : devices) {
                        int deviceScore = rateDeviceSuitability(device);
                        candidates.emplace(device, deviceScore);
                    }

                    VkPhysicalDevice bestDevice = VK_NULL_HANDLE;
                    int highestScore = -1;

                    for (const auto& candidate : candidates) {
                        if (candidate.second > highestScore) {
                            bestDevice = candidate.first;
                            highestScore = candidate.second;
                        }
                    }

                    // Use the best device
                    physicalDevice = bestDevice;

                }

                const VkPhysicalDevice& VulkanDevice::getPhysicalDevice() const {
                    return physicalDevice;
                }

                int VulkanDevice::rateDeviceSuitability(VkPhysicalDevice device) {
                    VkPhysicalDeviceProperties deviceProperties;
                    VkPhysicalDeviceFeatures deviceFeatures;
                    vkGetPhysicalDeviceProperties(device, &deviceProperties);
                    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

                    int score = 0;

                    spdlog::debug("Evaluating device: {}", deviceProperties.deviceName);

                    // Geometry shaders are essential
                    if (!deviceFeatures.geometryShader) {
                        spdlog::debug("Device does not support geometry shader. Device is not suitable.");
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

                    score += deviceProperties.limits.maxViewports;
                    score += deviceProperties.limits.maxImageDimension1D;
                    score += deviceProperties.limits.maxImageDimension2D;
                    score += deviceProperties.limits.maxImageDimension3D;
                    score += deviceProperties.limits.maxCullDistances;

                    spdlog::debug("Device limits:");
                    spdlog::debug("  Max Viewports: {}", deviceProperties.limits.maxViewports);
                    spdlog::debug("  Max Image Dimension 1D: {}", deviceProperties.limits.maxImageDimension1D);
                    spdlog::debug("  Max Image Dimension 2D: {}", deviceProperties.limits.maxImageDimension2D);
                    spdlog::debug("  Max Image Dimension 3D: {}", deviceProperties.limits.maxImageDimension3D);
                    spdlog::debug("  Max Cull Distances: {}", deviceProperties.limits.maxCullDistances);

                    spdlog::debug("Device final suitability score: {}", score);

                    return score;
                }
                VulkanDevice::~VulkanDevice() {

                }
            }
        }
    }
}
