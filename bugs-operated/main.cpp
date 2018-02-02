#include "Core.h"

#include "MainMenu.h"

int main() {
	Core::Parameters parameters;
	parameters.width = 1024;
	parameters.height = 768;
	parameters.title = "bugs-operated";
	parameters.vsync = true;
	Core::init(parameters);

	try {
		SceneManager::addScene<MainMenu>();

		Core::run();
	}
	catch (const std::exception& e) {
		Log::write("Error:", e.what());
	}

	Core::close();

	return 0;
}
