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
#include "vector2_aux.hpp"

double sin(Vector2 v) {
	return v.y / sqrt(v.x*v.x + v.y*v.y);
}

double cos(Vector2 v) {
	return v.x / sqrt(v.x*v.x + v.y*v.y);
}

double tan(Vector2 v) {
	return v.y / v.x;
}

//return the amount to move
Vector2 projectCollisionVectorH(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	//length of a, c
	double a = std::min(std::abs(boxLeft - origin.x), std::abs(boxRight - origin.x));
	double c = a / cos(motion); //NOTE: B and motion are equivilent

	//if motion vector is too short for a collision
	if (std::abs(c) > motion.Length()) {
		return motion;
	}

	//is A within the box's bounds?
	Vector2 A = motion * std::abs(a);
	if ((A + origin).y >= boxTop && (A + origin).y <= boxBottom) {
		//if so, scale A down so that the new x is 1 unit outside of the box
		return motion * ((a>0 ? a-1 : a+1) / motion.x);
	}
	else {
		//if not, return the normal end point
		return motion;
	}
}

//return the amount to move
Vector2 projectCollisionVectorV(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	//length of a, c
	double a = std::min(std::abs(boxTop - origin.y), std::abs(boxBottom - origin.y));
	double c = a / sin(motion); //NOTE: B and motion are equivilent

	//if motion vector is too short for a collision
	if (std::abs(c) > motion.Length()) {
		return motion;
	}

	//is A within the box's bounds?
	Vector2 A = motion * std::abs(a);
	if ((A + origin).x >= boxLeft && (A + origin).x <= boxRight) {
		//if so, scale A down so that the new y is 1 unit outside of the box
		return motion * ((a>0 ? a-1 : a+1) / motion.y);
	}
	else {
		//if not, return the normal end point
		return motion;
	}
}

Vector2 projectCollisionVector(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	Vector2 h = projectCollisionVectorH(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	Vector2 v = projectCollisionVectorV(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	return h.SquaredLength() > v.SquaredLength() ? h : v;
}