#include "VulkanInstance.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            VulkanInstance::VulkanInstance() : instance(VK_NULL_HANDLE) {

            }

            void VulkanInstance::create(const std::string& appName, uint32_t appVersion) {
                // Specify application info for Vulkan instance creation
                VkApplicationInfo appInfo{};
                appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName = appName.c_str();        // Name of the application
                appInfo.applicationVersion = appVersion;           // Version of the application
                appInfo.pEngineName = ENGINE_NAME;                 // Engine name from MakerEngine header
                appInfo.engineVersion = ENGINE_VERSION;            // Engine version from MakerEngine header
                appInfo.apiVersion = VULKAN_API_VERSION;           // Vulkan API version from MakerEngine header

                // Setup Vulkan instance creation info
                VkInstanceCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                createInfo.pApplicationInfo = &appInfo;

                // Setup extensions
                std::vector<const char*> extensions;

                // Retrieve required GLFW extensions for Vulkan
                uint32_t glfwExtensionCount = 0;
                const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

                // Add GLFW extensions to the list of extensions
                for (uint32_t i = 0; i < glfwExtensionCount; i++) {
                    extensions.emplace_back(glfwExtensions[i]);
                }

                // On macOS we will need VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR and
                // VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
                #ifdef PLATFORM_MACOS
                    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
                    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
                #endif      

                createInfo.enabledExtensionCount = (uint32_t)extensions.size();
                createInfo.ppEnabledExtensionNames = extensions.data();

                // Validation layers
                std::vector<const char*> validationLayers = {
                    "VK_LAYER_KHRONOS_validation"
                };

                #ifdef MAKERENGINE_DEBUG
                    const bool enableValidationLayers = true;
                #else
                    const bool enableValidationLayers = false;
                #endif

                if (enableValidationLayers && !checkValidationLayerSupport()) {
                    spdlog::critical("Validation layers requested, but not available!");
                    throw std::runtime_error("Validation layers requested, but not available!");
                }

                if (enableValidationLayers) {
                    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                    createInfo.ppEnabledLayerNames = validationLayers.data();
                }
                else {
                    createInfo.enabledLayerCount = 0;
                }

                // Create the Vulkan instance
                VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
                if (result != VK_SUCCESS) {
                    spdlog::critical("Failed to create Vulkan instance!");
                    throw std::runtime_error("Failed to create Vulkan instance!");
                }

                // Enumerate all available Vulkan extensions
                uint32_t extensionCount = 0;
                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

                std::vector<VkExtensionProperties> availableExtensions(extensionCount);
                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

                for (const auto& extension : availableExtensions) {
                    spdlog::debug("Available Vulkan extension: {}", extension.extensionName);
                }

                // Log Vulkan instance creation success and app info
                spdlog::debug("Vulkan instance created successfully");
                spdlog::debug("App Info Data:");
                spdlog::debug("pApplicationName: {}", appInfo.pApplicationName);
                spdlog::debug("applicationVersion: {}", appInfo.applicationVersion);
                spdlog::debug("pEngineName: {}", appInfo.pEngineName);
                spdlog::debug("engineVersion: {}", appInfo.engineVersion);
                spdlog::debug("apiVersion: {}", appInfo.apiVersion);
            }

            bool VulkanInstance::checkValidationLayerSupport() {
                uint32_t layerCount;
                vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

                std::vector<VkLayerProperties> availableLayers(layerCount);
                vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

                for (const auto& layer : availableLayers) {
                    if (strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0) {
                        return true;
                    }
                }

                return false;
            }

            void VulkanInstance::destroy() {
                if (instance != VK_NULL_HANDLE) {
                    vkDestroyInstance(instance, nullptr);
                    spdlog::debug("Vulkan instance destroyed");
                }
            }

            VulkanInstance::~VulkanInstance() {
                destroy();
            }
        }
    }
}
