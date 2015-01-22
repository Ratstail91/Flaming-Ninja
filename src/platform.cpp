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
#include "platform.hpp"

void Platform::DrawTo(SDL_Surface* const dest, int camX, int camY) {
	//Use SDL to draw a black box
	SDL_Rect rect;
	rect.x = origin.x + bounds.x - camX;
	rect.y = origin.y + bounds.y - camY;
	rect.w = bounds.w;
	rect.h = bounds.h;
	SDL_FillRect(dest, &rect, SDL_MapRGB(dest->format, 0, 0, 0));
}

Vector2 Platform::SetOrigin(Vector2 v) {
	return origin = v;
}

Vector2 Platform::GetOrigin() {
	return origin;
}

BoundingBox Platform::SetBounds(BoundingBox b) {
	return bounds = b;
}

BoundingBox Platform::GetBounds() {
	return bounds;
}

