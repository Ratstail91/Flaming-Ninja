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
#include "player.hpp"

void Player::DrawTo(SDL_Surface* const dest, int camX, int camY) {
	//Use SDL to draw a red box
	SDL_Rect rect;
	rect.x = origin.x;
	rect.y = origin.y;
	rect.w = 32;
	rect.h = 32;
	SDL_FillRect(dest, &rect, SDL_MapRGB(dest->format, 255, 0, 0));
}

//-------------------------
//accessors & mutators
//-------------------------

Vector2 Player::SetOrigin(Vector2 v) {
	return origin = v;
}

Vector2 Player::ShiftOrigin(Vector2 v) {
	return origin += v;
}

Vector2 Player::GetOrigin() {
	return origin;
}

Vector2 Player::SetMotion(Vector2 v) {
	return motion = v;
}

Vector2 Player::ShiftMotion(Vector2 v) {
	return motion += v;
}

Vector2 Player::GetMotion() {
	return motion;
}

//-------------------------
//more granular accessors & mutators
//-------------------------

double Player::SetOriginX(double d) {
	return origin.x = d;
}

double Player::SetOriginY(double d) {
	return origin.y = d;
}

double Player::ShiftOriginX(double d) {
	return origin.x += d;
}

double Player::ShiftOriginY(double d) {
	return origin.y += d;
}

double Player::GetOriginX() {
	return origin.x;
}

double Player::GetOriginY() {
	return origin.y;
}

double Player::SetMotionX(double d) {
	return motion.x = d;
}

double Player::SetMotionY(double d) {
	return motion.y = d;
}

double Player::ShiftMotionX(double d) {
	return motion.x += d;
}

double Player::ShiftMotionY(double d) {
	return motion.y += d;
}

double Player::GetMotionX() {
	return motion.x;
}

double Player::GetMotionY() {
	return motion.y;
}
