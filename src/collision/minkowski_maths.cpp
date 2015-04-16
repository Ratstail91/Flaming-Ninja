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
#include "minkowski.hpp"

double sin(Vector2 v) {
	return v.y / sqrt(v.x*v.x + v.y*v.y);
}

double cos(Vector2 v) {
	return v.x / sqrt(v.x*v.x + v.y*v.y);
}

double tan(Vector2 v) {
	return v.y / v.x;
}

std::list<BoundingBox> sweepBoxList(std::list<BoundingBox> boxList, BoundingBox charBounds) {
	for (auto& it : boxList) {
		it.x -= charBounds.w / 2;
		it.y -= charBounds.h / 2;
		it.w += charBounds.w;
		it.h += charBounds.h;
	}
	return boxList;
}

void calcCollision(Vector2& origin, Vector2& motion, std::list<BoundingBox> boxList) {
	if (motion == 0) {
		return;
	}

	//setup vectors to work on
	Vector2 shortestMotion = motion;
	Vector2 deflectedMotion = {0, 0};

	//TODO
}