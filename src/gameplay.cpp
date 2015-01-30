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

constexpr double gravity = 0.05;
constexpr double terminal = 6.0;
constexpr double moveSpeed = 2.0;
constexpr double jumpSpeed = 4.0;

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
	//gravity
	if (player.GetMotionY() < terminal) {
		player.ShiftMotionY(gravity);
	}
	if (player.GetMotionY() >= terminal) {
		player.SetMotionY(terminal);
	}
	player.ShiftOriginX(player.GetMotionX());
}

void Gameplay::FrameEnd() {
	//
}

void Gameplay::RenderFrame() {
	Render(GetScreen());
	SDL_Flip(GetScreen());
	SDL_Delay(10);
}

void Gameplay::Render(SDL_Surface* const screen) {
	//white background
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

	//draw the platforms
	for (auto& it : platformList) {
		it.DrawTo(screen, 0, 0);
	}

	//draw the selections
	if (drawSelection.pressed) {
		Selection tmp = drawSelection;
		tmp.CorrectAxis();
		tmp.DrawTo(screen, 0, 0);
	}
	if (dragSelection.pressed) {
		Selection tmp = dragSelection;
		tmp.CorrectAxis();
		tmp.DrawTo(screen, 0, 0);
	}

	//draw the player
	player.DrawTo(screen, 0, 0);
}

//-------------------------
//Event handlers
//-------------------------

void Gameplay::MouseMotion(SDL_MouseMotionEvent const& motion) {
	if (drawSelection.pressed) {
		drawSelection.w += motion.xrel;
		drawSelection.h += motion.yrel;
	}
	if (dragSelection.pressed) {
		dragSelection.x += motion.xrel;
		dragSelection.y += motion.yrel;
	}
}

void Gameplay::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	switch(button.button) {
		case SDL_BUTTON_LEFT:
			if (dragSelection.pressed) {
				break;
			}
			drawSelection.x = button.x;
			drawSelection.y = button.y;
			drawSelection.w = 0;
			drawSelection.h = 0;
			drawSelection.pressed = true;
		break;
		case SDL_BUTTON_RIGHT: {
			if (drawSelection.pressed) {
				break;
			}
			//compare
			BoundingBox mouseBox(button.x, button.y);
			BoundingBox platformBox;

			//get the drag selection
			for (std::list<Platform>::iterator it = platformList.begin(); it != platformList.end(); it++) {
				//bounds
				platformBox.x = it->GetX();
				platformBox.y = it->GetY();
				platformBox.w = it->GetW();
				platformBox.h = it->GetH();

				if (mouseBox.CheckOverlap(platformBox)) {
					dragSelection.x = it->GetX();
					dragSelection.y = it->GetY();
					dragSelection.w = it->GetW();
					dragSelection.h = it->GetH();
					platformList.erase(it);
					dragSelection.pressed = true;
					return;
				}
			}
		}
		break;
	}
}

void Gameplay::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	switch(button.button) {
		case SDL_BUTTON_LEFT:
			if (drawSelection.pressed) {
				//push the selection to the list
				drawSelection.CorrectAxis();
				platformList.emplace_back(drawSelection.x, drawSelection.y, drawSelection.w, drawSelection.h);
				drawSelection.Reset();
			}
		break;
		case SDL_BUTTON_RIGHT:
			if (dragSelection.pressed) {
				//drop the dragged selection to the list
				dragSelection.CorrectAxis();
				platformList.emplace_back(dragSelection.x, dragSelection.y, dragSelection.w, dragSelection.h);
				dragSelection.Reset();
			}
		break;
	}
}

void Gameplay::KeyDown(SDL_KeyboardEvent const& key) {
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;

		//player movement
		case SDLK_a:
			player.ShiftMotionX(-moveSpeed);
		break;
		case SDLK_d:
			player.ShiftMotionX(moveSpeed);
		break;
		case SDLK_SPACE:
			player.ShiftMotionY(-jumpSpeed);
		break;
	}
}

void Gameplay::KeyUp(SDL_KeyboardEvent const& key) {
	switch(key.keysym.sym) {
		//player movement (release)
		case SDLK_a:
			if (player.GetMotionX() + moveSpeed <= moveSpeed) {
				player.ShiftMotionX(moveSpeed);
			}
			else {
				player.SetMotionX(moveSpeed);
			}
		break;
		case SDLK_d:
			if (player.GetMotionX() - moveSpeed >= -moveSpeed) {
				player.ShiftMotionX(-moveSpeed);
			}
			else {
				player.SetMotionX(-moveSpeed);
			}
		break;
	}
}

//-------------------------
//utilities
//-------------------------

void Gameplay::Selection::DrawTo(SDL_Surface* const dest, int camX, int camY) {
	//Use SDL to draw a black box
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FillRect(dest, &rect, SDL_MapRGB(dest->format, 86, 61, 228));
}

void Gameplay::Selection::CorrectAxis() {
	//check for and correct negatives
	if (w < 0) {
		w = -w;
		x = x - w;
	}
	if (h < 0) {
		h = -h;
		y = y - h;
	}
}

void Gameplay::Selection::Reset() {
	x = y = w = h = -1;
	pressed = false;
}