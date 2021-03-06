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
#include "entity.hpp"

Entity::Entity() {
	origin = {0, 0};
	motion = {0, 0};
	bounds = {0, 0, 0, 0};
}

Entity::~Entity() {
	//
}

void Entity::Update() {
	origin += motion;
}

void Entity::DrawTo(SDL_Surface* const dest, Sint16 camX, Sint16 camY) {
	image.DrawTo(dest, origin.x + camX, origin.y + camY);
}

Image* Entity::GetImage() {
	return &image;
}

Vector2 Entity::SetOrigin(Vector2 v) {
	return origin = v;
}

Vector2 Entity::ShiftOrigin(Vector2 v) {
	return origin += v;
}

Vector2 Entity::GetOrigin() {
	return origin;
}

Vector2 Entity::SetMotion(Vector2 v) {
	return motion = v;
}

Vector2 Entity::ShiftMotion(Vector2 v) {
	return motion += v;
}

Vector2 Entity::GetMotion() {
	return motion;
}

BoundingBox Entity::SetBounds(BoundingBox b) {
	return bounds = b;
}

BoundingBox Entity::GetBounds() {
	return bounds;
}
