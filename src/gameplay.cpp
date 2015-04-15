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
#include "gameplay.hpp"

//-------------------------
//Public access members
//-------------------------

Gameplay::Gameplay() {
	//singleton alias
	ConfigUtility& config = ConfigUtility::GetSingleton();

	//load the images
	player.GetImage()->LoadSurface(config["dir.graphics"] + "player.bmp");
	blockTemplate.LoadSurface(config["dir.graphics"] + "brick.bmp");

	//generate the ground
	for (int i = 0; i < 10; i++) {
		blockList.emplace_front();
		blockList.front().SetOrigin({i * 32.0, 568.0});
		blockList.front().GetImage()->SetSurface(blockTemplate.GetSurface());
		blockList.front().SetBounds({0, 0, blockTemplate.GetClipW(), blockTemplate.GetClipH()});
	}
}

Gameplay::~Gameplay() {
	//
}

//-------------------------
//Frame loop
//-------------------------

void Gameplay::FrameStart() {
	//
}

void Gameplay::Update() {
	//
}

void Gameplay::FrameEnd() {
	//
}

void Gameplay::Render(SDL_Surface* const screen) {
	for (auto& it : blockList) {
		it.GetImage()->DrawTo(screen, it.GetOrigin().x, it.GetOrigin().y);
	}
}

//-------------------------
//Event handlers
//-------------------------

void Gameplay::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void Gameplay::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//
}

void Gameplay::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void Gameplay::KeyDown(SDL_KeyboardEvent const& key) {
	//
}

void Gameplay::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
