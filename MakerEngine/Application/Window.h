#pragma once

#include "MakerEngine.h"

#include <spdlog/spdlog.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace MakerEngine {
    namespace Application {
        class MAKERENGINE_API Window {
        public:
            Window();
            ~Window();

            void create(int width, int height, const std::string& name);

            void runLoop();

            GLFWwindow* getHandle() const;

            int getWidth() const;
            int getHeight() const;

            const std::string& getName() const;

        private:
            void destroy();

            GLFWwindow* window;

            int width;
            int height;

            std::string name;
        };
    }
}
