#include "Core.h"

#include "Intro.h"
#include "Game.h"

/*
                       _______________
					   |             |
      _                |   GOVNOKOD  |
      \\       /\_/\   |_  __________|
       \\_____< * \ *>   |/
       /  ___  \__()/__
       |_____\---\_____\

   ( говорящий правду. сфинкс-енот )
*/


int main() {
	Core::Parameters parameters;
	parameters.width = 1024;
	parameters.height = 768;
	parameters.title = "bugs-operated";
	parameters.vsync = true;
	Core::init(parameters);

	try {
		SceneManager::addScene<Game>();

		Core::run();
	}
	catch (const std::exception& e) {
		Log::write("Error:", e.what());
	}

	Core::close();

	return 0;
}
