#pragma once

#include "MakerEngine.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <cstring>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                class MAKERENGINE_API VulkanInstance {
                public:
                    VulkanInstance();
                    ~VulkanInstance();

                    void create(const std::string& appName, const uint32_t appVersion);

                    VkInstance getHandle() const;

                private:
                    bool checkValidationLayerSupport();

                    std::vector<const char*> getRequiredExtensions();

                    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                        void* pUserData
                    );

                    VkResult CreateDebugUtilsMessengerEXT(
                        VkInstance instance,
                        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                        const VkAllocationCallbacks* pAllocator,
                        VkDebugUtilsMessengerEXT* pDebugMessenger
                    );

                    void DestroyDebugUtilsMessengerEXT(
                        VkInstance instance,
                        VkDebugUtilsMessengerEXT debugMessenger,
                        const VkAllocationCallbacks* pAllocator
                    );

                    void createDebugMessenger();

                    void destroy();

                    bool enableValidationLayers;
                    VkDebugUtilsMessengerEXT debugMessenger;
                    VkInstance instance;
                };
            }
        }
    }
}
