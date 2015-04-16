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
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "bounding_box.hpp"
#include "image.hpp"
#include "vector2.hpp"

class Entity {
public:
	Entity();
	~Entity();

	void Update();
	void DrawTo(SDL_Surface* const dest, Sint16 camX, Sint16 camY);

	Image* GetImage();

	Vector2 SetOrigin(Vector2 v);
	Vector2 ShiftOrigin(Vector2 v);
	Vector2 GetOrigin();
	Vector2 SetMotion(Vector2 v);
	Vector2 ShiftMotion(Vector2 v);
	Vector2 GetMotion();
	BoundingBox SetBounds(BoundingBox b);
	BoundingBox GetBounds();

private:
	Image image;
	Vector2 origin;
	Vector2 motion;
	BoundingBox bounds;
};

#endif