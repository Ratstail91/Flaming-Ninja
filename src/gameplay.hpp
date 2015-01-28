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
#ifndef GAMEPLAY_HPP_
#define GAMEPLAY_HPP_

#include "base_scene.hpp"
#include "platform.hpp"
#include "player.hpp"

#include <list>

class Gameplay: public BaseScene {
public:
	//Public access members
	Gameplay();
	~Gameplay();

protected:
	//Frame loop
	void FrameStart();
	void Update();
	void FrameEnd();
	void RenderFrame();
	void Render(SDL_Surface* const);

	//Event handlers
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&);
	void KeyDown(SDL_KeyboardEvent const&);
	void KeyUp(SDL_KeyboardEvent const&);

	//members
	std::list<Platform> platformList;

	struct Selection {
		int x = -1, y = -1;
		int w = -1, h = -1;
		bool pressed = false;
		void CorrectAxis();
		void DrawTo(SDL_Surface* const dest, int camX, int camY);
	} selection;

	Player player;
};

#endif
