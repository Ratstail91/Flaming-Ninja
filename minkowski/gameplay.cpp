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

#include <iostream>

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
//	if (player.GetMotionY() < terminal) {
//		player.ShiftMotionY(gravity);
//	}
//	if (player.GetMotionY() >= terminal) {
//		player.SetMotionY(terminal);
//	}
//	player.ShiftOrigin(player.GetMotion());

	//check collisions & move
	//NOTE: magic numbers for the player's bounding box
	//NOTE: the player's bounding box has one less pixel on the sides, a side effect of the vector2_aux.cpp algorithm
	std::list<BoundingBox> boxList = CalcBoxList();
	SweepBoxList(boxList, {1, 1, 30, 30});
	Vector2 epsilon(16, 16);
	player.SetOrigin(ProjectCollisionVector(player.GetOrigin() + epsilon, player.GetMotion(), boxList) - epsilon);

	std::cout << player.GetOriginX() << ", " << player.GetOriginY() << std::endl;
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

	//*DEBUG: draw the boxList
	std::list<BoundingBox> boxList = CalcBoxList();
	SweepBoxList(boxList, BoundingBox(0, 0, 32, 32));
	for (auto& it : boxList) {
		SDL_Rect rect;
		rect.x = it.x;
		rect.y = it.y;
		rect.w = it.w;
		rect.h = it.h;
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 255));
	}//*/

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
		case SDL_BUTTON_MIDDLE:
			//delete this platform
			if (drawSelection.pressed) {
				drawSelection.Reset();
			}
			if (dragSelection.pressed) {
				dragSelection.Reset();
			}
			//compare
			BoundingBox mouseBox(button.x, button.y);
			BoundingBox platformBox;

			//get the platform under the hover
			for (std::list<Platform>::iterator it = platformList.begin(); it != platformList.end(); it++) {
				//bounds
				platformBox.x = it->GetX();
				platformBox.y = it->GetY();
				platformBox.w = it->GetW();
				platformBox.h = it->GetH();

				if (mouseBox.CheckOverlap(platformBox)) {
					platformList.erase(it);
					return;
				}
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
		case SDLK_w:
			player.ShiftMotionY(-moveSpeed);
		break;
		case SDLK_a:
			player.ShiftMotionX(-moveSpeed);
		break;
		case SDLK_s:
			player.ShiftMotionY(moveSpeed);
		break;
		case SDLK_d:
			player.ShiftMotionX(moveSpeed);
		break;
//		case SDLK_SPACE:
//			player.ShiftMotionY(-jumpSpeed);
//		break;
	}
}

void Gameplay::KeyUp(SDL_KeyboardEvent const& key) {
	switch(key.keysym.sym) {
		//player movement (release)
		case SDLK_w:
			if (player.GetMotionY() + moveSpeed <= moveSpeed) {
				player.ShiftMotionY(moveSpeed);
			}
			else {
				player.SetMotionY(moveSpeed);
			}
		break;
		case SDLK_a:
			if (player.GetMotionX() + moveSpeed <= moveSpeed) {
				player.ShiftMotionX(moveSpeed);
			}
			else {
				player.SetMotionX(moveSpeed);
			}
		break;
		case SDLK_s:
			if (player.GetMotionY() - moveSpeed >= -moveSpeed) {
				player.ShiftMotionY(-moveSpeed);
			}
			else {
				player.SetMotionY(-moveSpeed);
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
		case SDLK_1:
			player.SetOrigin({0, 0});
			player.SetMotion({0, 0});
		break;
	}
}

//-------------------------
//utilities
//-------------------------

std::list<BoundingBox> Gameplay::CalcBoxList() {
	std::list<BoundingBox> boxList;
	for (auto& it : platformList) {
		boxList.emplace_back(it.GetX(), it.GetY(), it.GetW(), it.GetH());
	}
	return boxList;

}

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

//-------------------------
//Maths
//-------------------------

//NOTE: the box list should be pre-computed as absolute collision areas

void Gameplay::SweepBoxList(std::list<BoundingBox>& boxList, BoundingBox box) {
	//minkowski sum; blame handmade hero
	for (auto& it : boxList) {
		it.x -= box.w / 2;
		it.y -= box.h / 2;
		it.w += box.w;
		it.h += box.h;
	}
}

//NOTE: The origin here MUST be the center of the swepted box, not the raw origin of the player object
Vector2 Gameplay::ProjectCollisionVector(Vector2 origin, Vector2 motion, std::list<BoundingBox> boxList) {
	//check for a lack of movement
	if (motion == 0) {
		return origin;
	}

	Vector2 shortestMotion = motion;
	Vector2 deflectedMotion = {0, 0};

	//check if the motion vector passes through a box area
	for (auto& box : boxList) {
		//TODO: if so, calculate the "shortest" motion possible
		shortestMotion = projectCollisionVector(origin, shortestMotion, box.x, box.x + box.w, box.y, box.y + box.h);

		//TODO: then, calculate the deflection
		//TODO: account for a "shortest" projection of 0 (collided at 90°)
	}

	return origin + shortestMotion;
}
