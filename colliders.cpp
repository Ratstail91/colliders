#include "colliders.hpp"

#include <type_traits>

//These are explicitly PODs
static_assert(std::is_pod<ColliderLine>::value, "ColliderLine is not a POD");
static_assert(std::is_pod<ColliderCircle>::value, "ColliderCircle is not a POD");
static_assert(std::is_pod<ColliderBox>::value, "ColliderBox is not a POD");
static_assert(std::is_pod<ColliderPoint>::value, "ColliderPoint is not a POD");

//vector shifts and assignments
ColliderLine operator+(ColliderLine const& lhs, Vector2 const& rhs) {
	return ColliderLine{{lhs.center + rhs}, {lhs.projection + rhs}};
}

ColliderCircle operator+(ColliderCircle const& lhs, Vector2 const& rhs) {
	return ColliderCircle{{lhs.center + rhs}, lhs.radius};
}

ColliderBox operator+(ColliderBox const& lhs, Vector2 const& rhs) {
	return ColliderBox{{lhs.center + rhs}, lhs.halfSize};
}

ColliderPoint operator+(ColliderPoint const& lhs, Vector2 const& rhs) {
	return ColliderPoint{{lhs.center + rhs}};
}

ColliderLine& operator+=(ColliderLine& lhs, Vector2 const& rhs) {
	return lhs = lhs + rhs;
}

ColliderCircle& operator+=(ColliderCircle& lhs, Vector2 const& rhs) {
	return lhs = lhs + rhs;
}

ColliderBox& operator+=(ColliderBox& lhs, Vector2 const& rhs) {
	return lhs = lhs + rhs;
}

ColliderPoint& operator+=(ColliderPoint& lhs, Vector2 const& rhs) {
	return lhs = lhs + rhs;
}

//lines
bool Intersect(ColliderLine const& lhs, ColliderLine const& rhs) {
	//this algorithm was copied from the net, so I'm not messing with it
	const double x1 = lhs.center.x;
	const double y1 = lhs.center.y;
	const double x2 = lhs.projection.x;
	const double y2 = lhs.projection.y;
	const double x3 = rhs.center.x;
	const double y3 = rhs.center.y;
	const double x4 = rhs.projection.x;
	const double y4 = rhs.projection.y;

	//calculate the direction of the lines
	const double uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	const double uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	//if uA and uB are between 0-1, lines are colliding
	return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}

bool Intersect(ColliderLine const& line, ColliderCircle const& circle) {
	//check the end-points (short-circuit)
	if (Intersect(ColliderPoint{{line.center.x, line.center.y}}, circle) || Intersect(ColliderPoint{{line.projection.x, line.projection.y}}, circle)) {
		return true;
	}

	//length of the line
	const double length = Vector2{line.projection.x - line.center.x, line.projection.y - line.center.y}.Length();

	//dot product of the line & circle
	const double dot = ( ((circle.center.x-line.center.x)*(line.projection.x-line.center.x)) + ((circle.center.y-line.center.y)*(line.projection.y-line.center.y)) ) / pow(length, 2);

	//find the closest point on the line
	const double closestX = line.center.x + (dot * (line.projection.x-line.center.x));
	const double closestY = line.center.y + (dot * (line.projection.y-line.center.y));

	//is this point actually on the line segment? if so keep going, but if not, return false
	const bool onSegment = Intersect(line, ColliderPoint{{closestX, closestY}});
	if (!onSegment) {
		return false;
	}

	//get distance to closest point
	const double distX = closestX - circle.center.x;
	const double distY = closestY - circle.center.y;
	const double distance = sqrt(pow(distX, 2) + pow(distY, 2));

	//use a buffer for floating point innacuracies
	const double buffer = 0.0001;

	//finally
	return distance <= circle.radius + buffer;
}

bool Intersect(ColliderLine const& line, ColliderBox const& box) {
	//check the end points
	const bool centerIntersects = Intersect(ColliderPoint{{line.center.x, line.center.y}}, box);
	const bool projectionIntersects = Intersect(ColliderPoint{{line.projection.x, line.projection.y}}, box);

	if (centerIntersects || projectionIntersects) {
		return true;
	}

	//get the box corners
	const Vector2 a = Vector2{box.center.x - box.halfSize.x, box.center.y - box.halfSize.y};
	const Vector2 b = Vector2{box.center.x - box.halfSize.x, box.center.y + box.halfSize.y};
	const Vector2 c = Vector2{box.center.x + box.halfSize.x, box.center.y - box.halfSize.y};
	const Vector2 d = Vector2{box.center.x + box.halfSize.x, box.center.y + box.halfSize.y};

	//test each box line
	const bool lineAB = Intersect(line, ColliderLine{a, b});
	const bool lineAC = Intersect(line, ColliderLine{a, c});
	const bool lineCD = Intersect(line, ColliderLine{c, d});
	const bool lineBD = Intersect(line, ColliderLine{b, d});

	return lineAB || lineAC || lineCD || lineBD;
}

bool Intersect(ColliderLine const& line, ColliderPoint const& point) {
	//get distance from the point to the two ends of the line
	const double d1 = (point.center - line.center).Length();
	const double d2 = (point.center - line.projection).Length();

	//use a buffer due to floating point innacuracies
	const double length = (line.projection - line.center).Length();
	const double buffer = 0.0001;

	//interesting trick
	return d1 + d2 >= length - buffer && d1 + d2 <= length + buffer;
}

//circles
bool Intersect(ColliderCircle const& lhs, ColliderLine const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderCircle const& lhs, ColliderCircle const& rhs) {
	return (rhs.center - lhs.center).SquaredLength() <= pow(lhs.radius + rhs.radius, 2);
}

bool Intersect(ColliderCircle const& circle, ColliderBox const& box) {
	//temporary variables to set edges for testing
	double testX = circle.center.x;
	double testY = circle.center.y;

	//which edge is closest?
	if (circle.center.x < box.center.x - box.halfSize.x) {
		testX = box.center.x - box.halfSize.x;
	}
	else if (circle.center.x > box.center.x + box.halfSize.x) {
		testX = box.center.x + box.halfSize.x;
	}

	if (circle.center.y < box.center.y - box.halfSize.y) {
		testY = box.center.y - box.halfSize.y;
	}
	else if (circle.center.y > box.center.y + box.halfSize.y) {
		testY = box.center.y + box.halfSize.y;
	}

	double distX = circle.center.x - testX;
	double distY = circle.center.y - testY;
	double distance = sqrt(pow(distX, 2) + pow(distY, 2));

	return distance <= circle.radius;
}

bool Intersect(ColliderCircle const& lhs, ColliderPoint const& rhs) {
	return (rhs.center - lhs.center).SquaredLength() <= pow(lhs.radius, 2);
}

//boxes
bool Intersect(ColliderBox const& lhs, ColliderLine const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderBox const& lhs, ColliderCircle const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderBox const& lhs, ColliderBox const& rhs) {
	//x-direction
	if (lhs.center.x - lhs.halfSize.x > rhs.center.x + rhs.halfSize.x) {
		return false;
	}

	if (lhs.center.x + lhs.halfSize.x < rhs.center.x - rhs.halfSize.x) {
		return false;
	}

	//y-direction
	if (lhs.center.y - lhs.halfSize.y > rhs.center.y + rhs.halfSize.y) {
		return false;
	}

	if (lhs.center.y + lhs.halfSize.y < rhs.center.y - rhs.halfSize.y) {
		return false;
	}

	return true;
}

bool Intersect(ColliderBox const& box, ColliderPoint const& point) {
	//x-direction
	if (point.center.x < box.center.x - box.halfSize.x) {
		return false;
	}

	if (point.center.x > box.center.x + box.halfSize.x) {
		return false;
	}

	//x-direction
	if (point.center.y < box.center.y - box.halfSize.y) {
		return false;
	}

	if (point.center.y > box.center.y + box.halfSize.y) {
		return false;
	}

	return true;
}

//points
bool Intersect(ColliderPoint const& lhs, ColliderLine const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderPoint const& lhs, ColliderCircle const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderPoint const& lhs, ColliderBox const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderPoint const& lhs, ColliderPoint const& rhs) {
	return lhs.center == rhs.center;
}