#include "Window.h"

namespace MakerEngine {
	namespace Application {
		Window::Window() : window(nullptr), width(500), height(500), name("Default Window Title") {

		}

		void Window::create(int width, int height, const std::string& name) {
			this->width = width;
			this->height = height;
			this->name = name;

            // GLFW is already initialized in the Engine class, no need to initialize it here

			// Since we are using Vulkan, disable OpenGL context creation
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
			if (window == nullptr) {
				spdlog::critical("Failed to create window!");
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			spdlog::info("Window created successfully");
			spdlog::debug("Window size: {}x{}", width, height);
			spdlog::debug("Window name: {}", name.c_str());
		}

		void Window::destroy() {
			// Make sure the window is not nullptr before destroying it
			if (window) {
				glfwDestroyWindow(window);
				window = nullptr;
			}
		}

		void Window::runLoop() {
			spdlog::info("Main loop started");
			// Ensure the engine continues to run until the window is closed or something else happens
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}
		}

		GLFWwindow* Window::getWindow() const {
			return window;
		}

		int Window::getWidth() const {
			return width;
		}

		int Window::getHeight() const {
			return height;
		}

		const std::string& Window::getName() const {
			return name;
		}


		Window::~Window() {
			destroy();
			glfwTerminate();
		}
	}
}
