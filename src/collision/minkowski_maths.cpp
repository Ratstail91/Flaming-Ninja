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
#include "minkowski_maths.hpp"

/* DOCS: Explanation of the minkowski collision algorithms used here
 * 
 * Diagram 1:
 * 
	      B
	     /|
	  c / | a
	   /  |
	  A---C
	    b
 * 
 * This triangle is a right angle triangle, with A at the entity origin, B is
 * the end point of the motion vector, and C is a right-angle. Each corner is
 * denoted with a capital letter (A, B and C), while the opposite line is
 * denoted by a lowercase letter (a, b and c respectively).
 * 
 * The mathematical operations here are preformed on structures that have been
 * subjected to a minkowski sum i.e. the walls have had the entity's bounds
 * added to them. The purpose of these algorithms are to determine how the
 * entity is to move. The ideal behaviour is to allow the entity to move along
 * the original motion vector as far as possible, before deflecting it's
 * movement in a new direction, and repeating the process. If the motion vector
 * would terminate early at a 90° angle, then the motion can stop there.
 * 
 * Some known bugs are a tendancy for the entity to "stick" to the walls, as
 * well as motions of {0, 0} breaking the algorithm as a whole.
*/

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

/* DOCS: (Continued)
 * The algorithm starts at calcCollision(), which takes the origin, motion and
 * boxList as parameters. This applies the projection system to all given
 * boxes, as many times as needed.
*/

void calcCollision(Vector2& origin, Vector2& motion, std::list<BoundingBox> boxList) {
	//BUGFUX: ZERO motion
	if (motion == 0) {
		return;
	}

	//the temp vectors
	Vector2 shortestMotion = motion;
	Vector2 deflectedMotion = {0, 0};

	//check if the motion vector passes through a box area
	//if so, recieve the "shortest" motion possible
	//then, calculate the deflection
	//account for a "shortest" projection of 0 (collided at 90°)

	for (auto& box : boxList) {
		//TODO
	}
}

/* DOCS: (Continued)
 * Next...
*/