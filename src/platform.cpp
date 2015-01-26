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

Platform::Platform(int argX, int argY, int argW, int argH) {
	x = argX;
	y = argY;
	w = argW;
	h = argH;
}

void Platform::DrawTo(SDL_Surface* const dest, int camX, int camY) {
	//Use SDL to draw a black box
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FillRect(dest, &rect, SDL_MapRGB(dest->format, 0, 0, 0));
}

int Platform::SetX(int i) {
	return x = i;
}

int Platform::SetY(int i) {
	return y = i;
}

int Platform::SetW(int i) {
	return w = i;
}

int Platform::SetH(int i) {
	return h = i;
}

int Platform::GetX() {
	return x;
}

int Platform::GetY() {
	return y;
}

int Platform::GetW() {
	return w;
}

int Platform::GetH() {
	return h;
}
