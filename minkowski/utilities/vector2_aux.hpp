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
#ifndef VECTOR2AUX_HPP_
#define VECTOR2AUX_HPP_

#include "vector2.hpp"

double sin(Vector2 v);
double cos(Vector2 v);
double tan(Vector2 v);

Vector2 projectCollisionVectorH(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom);
Vector2 projectCollisionVectorV(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom);
Vector2 projectCollisionVector(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom);

#endif