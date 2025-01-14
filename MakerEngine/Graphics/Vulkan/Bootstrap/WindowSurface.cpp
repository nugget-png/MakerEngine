#include "WindowSurface.h"

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                WindowSurface::WindowSurface()
                    : surface(VK_NULL_HANDLE)
                {

                }

                void WindowSurface::create(const VulkanInstance& instance, const Application::Window& window) {
                    VkResult result =
                        glfwCreateWindowSurface(instance.getVkInstance(), window.getWindow(), nullptr, &surface);

                    if (result != VK_SUCCESS) {
                        spdlog::critical("Failed to create window surface!");
                        throw std::runtime_error("Failed to create window surface!");
                    }

                }

                void WindowSurface::destroy(const VulkanInstance& instance) {
                    vkDestroySurfaceKHR(instance.getVkInstance(), surface, nullptr);
                }
            }
        }
    }
}
