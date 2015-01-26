/* Copyright: (c) Kayne Ruse 2013-2015
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
	//
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

void Gameplay::RenderFrame() {
	SDL_FillRect(GetScreen(), 0, SDL_MapRGB(GetScreen()->format, 255, 255, 255));
	Render(GetScreen());
	SDL_Flip(GetScreen());
	SDL_Delay(10);
}

void Gameplay::Render(SDL_Surface* const screen) {
	for (auto& it : platformList) {
		it.DrawTo(screen, 0, 0);
	}
}

//-------------------------
//Event handlers
//-------------------------

void Gameplay::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void Gameplay::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	switch(button.button) {
		case SDL_BUTTON_LEFT:
			selected.x = button.x;
			selected.y = button.y;
			selected.pressed = true;
		break;
	}
}

void Gameplay::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	switch(button.button) {
		case SDL_BUTTON_LEFT:
			if (selected.pressed) {
				//basic
				Platform p(selected.x, selected.y, button.x - selected.x, button.y - selected.y);

				//check for and correct negatives
				if (p.GetW() < 0) {
					p.SetW(-p.GetW());
					p.SetX(p.GetX() - p.GetW());
				}
				if (p.GetH() < 0) {
					p.SetH(-p.GetH());
					p.SetY(p.GetY() - p.GetH());
				}

				//push
				platformList.push_back(p);

				//reset
				selected.x = -1;
				selected.y = -1;
				selected.pressed = false;
			}
		break;
	}
}

void Gameplay::KeyDown(SDL_KeyboardEvent const& key) {
	//hotkeys
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void Gameplay::KeyUp(SDL_KeyboardEvent const& key) {
	//
}
