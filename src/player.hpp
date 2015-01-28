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
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "SDL/SDL.h"
#include "vector2.hpp"

class Player {
public:
	Player() = default;
	~Player() = default;

	void DrawTo(SDL_Surface* const dest, int camX, int camY);

	//accessors & mutators
	Vector2 SetOrigin(Vector2);
	Vector2 ShiftOrigin(Vector2);
	Vector2 GetOrigin();

	Vector2 SetMotion(Vector2);
	Vector2 ShiftMotion(Vector2);
	Vector2 GetMotion();

	//more granular accessors & mutators
	double SetOriginX(double);
	double SetOriginY(double);
	double ShiftOriginX(double);
	double ShiftOriginY(double);
	double GetOriginX();
	double GetOriginY();

	double SetMotionX(double);
	double SetMotionY(double);
	double ShiftMotionX(double);
	double ShiftMotionY(double);
	double GetMotionX();
	double GetMotionY();

private:
	Vector2 origin;
	Vector2 motion;
};

#endif