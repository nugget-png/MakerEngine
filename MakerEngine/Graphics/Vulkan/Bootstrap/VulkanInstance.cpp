#include "VulkanInstance.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                VulkanInstance::VulkanInstance()
                    : instance(VK_NULL_HANDLE), enableValidationLayers(false), debugMessenger(VK_NULL_HANDLE)
                {

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

                    #ifdef MAKERENGINE_DEBUG
                        enableValidationLayers = true;
                    #else
                        enableValidationLayers = false;
                    #endif

                    // Get required extensions for this instance
                    auto extensions = getRequiredExtensions();
                    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
                    createInfo.ppEnabledExtensionNames = extensions.data();

                    // Validation layers
                    std::vector<const char*> validationLayers = {
                        "VK_LAYER_KHRONOS_validation"
                    };

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

                    // Create the debug messenger if validation layers are enabled
                    if (enableValidationLayers) {
                        createDebugMessenger();
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

                const VkInstance& VulkanInstance::getVkInstance() const {
                    return instance;
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

                std::vector<const char*> VulkanInstance::getRequiredExtensions() {
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

                    // Add debug utils extension if we are using validation layers
                    if (enableValidationLayers) {
                        extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                    }

                    return extensions;
                }

                VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::debugCallback(
                    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                    void* pUserData
                )

                {
                    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
                        spdlog::debug("Validation layer: (INFO) {}", pCallbackData->pMessage);
                    }
                    else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                        spdlog::warn("Validation layer: (WARNING) {}", pCallbackData->pMessage);
                    }
                    else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                        spdlog::error("Validation layer: (ERROR) {}", pCallbackData->pMessage);
                    }
                    else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                        spdlog::debug("Validation layer (VERBOSE): {}", pCallbackData->pMessage);
                    }

                    return VK_FALSE;
                }

                VkResult VulkanInstance::CreateDebugUtilsMessengerEXT(
                    VkInstance instance,
                    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                    const VkAllocationCallbacks* pAllocator,
                    VkDebugUtilsMessengerEXT* pDebugMessenger
                )

                {
                    auto function =
                        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

                    if (function != nullptr) {
                        function(instance, pCreateInfo, pAllocator, pDebugMessenger);
                    }
                    else {
                        return VK_ERROR_EXTENSION_NOT_PRESENT;
                    }

                    return VK_SUCCESS;
                }


                void VulkanInstance::DestroyDebugUtilsMessengerEXT(
                    VkInstance instance,
                    VkDebugUtilsMessengerEXT debugMessenger,
                    const VkAllocationCallbacks* pAllocator
                )

                {
                    auto function =
                        (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

                    if (function != nullptr) {
                        function(instance, debugMessenger, pAllocator);
                    }
                }

                void VulkanInstance::createDebugMessenger() {
                    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
                    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

                    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

                    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

                    createInfo.pfnUserCallback = debugCallback;
                    createInfo.pUserData = nullptr; // Not required

                    VkResult result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
                    if (result != VK_SUCCESS) {
                        spdlog::critical("Failed to create debug utils messenger ext!");
                        throw std::runtime_error("Failed to create debug utils messenger ext!");
                    }

                    spdlog::debug("Successfully created debug utils messenger ext");
                }

                void VulkanInstance::destroy() {
                    if (enableValidationLayers && debugMessenger != VK_NULL_HANDLE) {
                        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
                        spdlog::debug("Debug utils messenger ext destroyed");
                    }

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
}
