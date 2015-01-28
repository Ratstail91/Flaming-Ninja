/* Copyright: (c) Kayne Ruse 2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
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
#include <iostream>

int main(int argc, char* argv[]) {
	try {
		//create the singletons
		ConfigUtility::CreateSingleton();

		//call the application's routines
		Application::CreateSingleton();
		Application app = Application::GetSingleton();

		app.Init(argc, argv);
		app.Proc();
		app.Quit();

		Application::DeleteSingleton();

		//delete the singletons
		ConfigUtility::DeleteSingleton();
	}
	catch(std::exception& e) {
		std::cerr << "Fatal exception thrown: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}