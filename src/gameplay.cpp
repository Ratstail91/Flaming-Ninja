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

constexpr double gravityShift = 0.1;
constexpr double gravityMax = 5.0;

//-------------------------
//Public access members
//-------------------------

Gameplay::Gameplay() {
	//singleton alias
	ConfigUtility& config = ConfigUtility::GetSingleton();

	//setup the player
	player.GetImage()->LoadSurface(config["dir.graphics"] + "player.bmp");
	player.SetBounds({0, 0, player.GetImage()->GetClipW(), player.GetImage()->GetClipH()});

	//generate the ground
	blockTemplate.LoadSurface(config["dir.graphics"] + "brick.bmp");
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
	//player gravity
	if (player.GetMotion().y < gravityMax) {
		player.ShiftMotion({0, gravityShift});
	}
	else {
		//limit fall speed to terminal velocity
		Vector2 g = player.GetMotion();
		g.y = gravityMax;
		player.SetMotion(g);
	}

	//update the moving entities
	player.Update();

	//check collisions
	BoundingBox playerBox = player.GetBounds() + player.GetOrigin();
	for (auto& it : blockList) {
		BoundingBox blockBox = it.GetBounds() + it.GetOrigin();

		//collision
		if (playerBox.CheckOverlap(blockBox)) {
			//move the player back
			player.ShiftOrigin(player.GetMotion() * -1);

			//stop the motion
			player.SetMotion({0, 0});
		}
	}
}

void Gameplay::FrameEnd() {
	//
}

void Gameplay::Render(SDL_Surface* const screen) {
	for (auto& it : blockList) {
		it.DrawTo(screen, 0, 0);
	}

	player.DrawTo(screen, 0, 0);
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
