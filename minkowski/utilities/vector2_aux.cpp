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
	//BUGFIX: no motion
	if (motion == 0) {
		return motion;
	}

	//BUGIFX: moving away
	if (!BoundingBox(boxLeft, boxTop, boxRight-boxLeft, boxBottom-boxTop).CheckOverlap({int(origin.x+motion.x+motion.x), int(origin.y+motion.y+motion.y)})) {
		return motion;
	}

	//why only one direction?
	Vector2 h = projectCollisionVectorH(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	Vector2 v = projectCollisionVectorV(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	return h.SquaredLength() < v.SquaredLength() ? h : v;
}