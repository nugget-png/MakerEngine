#include <iostream>
#include <MakerEngine.h>

using namespace MakerEngine;

int main() {
	Engine engine;
	engine.initialize();

	spdlog::info("Ready");
	system("pause");

	engine.shutdown();
	return 0;
}