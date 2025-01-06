#include <iostream>
#include <MakerEngine.h>
#include <Application/Window.h>

using namespace MakerEngine;

int main() {
	Engine engine;
    Application::Window window;

	engine.initialize();

    window.create(1280, 720, "Game Player");
    window.runLoop();
    window.destroy();

	engine.shutdown();

	return 0;
}
