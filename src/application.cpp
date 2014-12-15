/* Copyright: (c) Kayne Ruse 2013, 2014
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial Applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "application.hpp"
#include "config_utility.hpp"

#include <stdexcept>
#include <chrono>
#include <iostream>

//-------------------------
//Scene headers
//-------------------------

//Add the custom scene headers here
#include "example.hpp"

//-------------------------
//Public access members
//-------------------------

void Application::Init(int argc, char* argv[]) {
	std::cout << "Beginning " << argv[0] << std::endl;

	//-------------------------
	//load the config file
	//-------------------------

	ConfigUtility& config = ConfigUtility::GetSingleton();
	config.Load("rsc/config.cfg", true, argc, argv);

	//-------------------------
	//Initialize the APIs
	//-------------------------

	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw(std::runtime_error("Failed to initialize SDL"));
	}
	std::cout << "Initialized SDL" << std::endl;

	//-------------------------
	//Setup the screen
	//-------------------------

	BaseScene::SetScreen(800, 600);
	std::cout << "Initialized the screen" << std::endl;

	//-------------------------
	//finalize the startup
	//-------------------------

	std::cout << "Startup completed successfully" << std::endl;

	//-------------------------
	//debugging
	//-------------------------

	//...
}

void Application::Proc() {
	LoadScene(SceneList::FIRST);

	//prepare the time system
	typedef std::chrono::steady_clock Clock;

	Clock::time_point simTime = Clock::now();
	Clock::time_point realTime;

	//The main loop
	while(activeScene->GetNextScene() != SceneList::QUIT) {
		//switch scenes when necessary
		if (activeScene->GetNextScene() != SceneList::CONTINUE) {
			LoadScene(activeScene->GetNextScene());
			continue;
		}

		//update the current time
		realTime = Clock::now();

		//simulate game time
		while (simTime < realTime) {
			//call each user defined function
			activeScene->RunFrame();
			//~60 FPS
			simTime += std::chrono::duration<int, std::milli>(16);
		}

		//draw the game to the screen
		activeScene->RenderFrame();
	}

	UnloadScene();
}

void Application::Quit() {
	std::cout << "Shutting down" << std::endl;
	SDL_Quit();
	std::cout << "Clean exit" << std::endl;
}

//-------------------------
//Private access members
//-------------------------

void Application::LoadScene(SceneList sceneIndex) {
	UnloadScene();
	switch(sceneIndex) {
		//add scene creation calls here
		case SceneList::FIRST:
		case SceneList::EXAMPLE:
			activeScene = new Example();
		break;
		default:
			throw(std::logic_error("Failed to recognize the scene index"));
	}
}

void Application::UnloadScene() {
	delete activeScene;
	activeScene = nullptr;
}
