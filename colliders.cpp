#include "colliders.hpp"

#include <type_traits>

//These are explicitly PODs
static_assert(std::is_pod<ColliderLine>::value, "ColliderLine is not a POD");
static_assert(std::is_pod<ColliderCircle>::value, "ColliderCircle is not a POD");
static_assert(std::is_pod<ColliderBox>::value, "ColliderBox is not a POD");
static_assert(std::is_pod<ColliderPoint>::value, "ColliderPoint is not a POD");

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
	double uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	double uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	//if uA and uB are between 0-1, lines are colliding
	return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}

bool Intersect(ColliderLine const& lhs, ColliderCircle const& rhs) {
	return false; //TODO
}

bool Intersect(ColliderLine const& lhs, ColliderBox const& rhs) {
	return false; //TODO
}

bool Intersect(ColliderLine const& lhs, ColliderPoint const& rhs) {
	return false; //TODO
}

//circles
bool Intersect(ColliderCircle const& lhs, ColliderLine const& rhs) {
	return Intersect(rhs, lhs);
}

bool Intersect(ColliderCircle const& lhs, ColliderCircle const& rhs) {
	return (rhs.center - lhs.center).SquaredLength() > lhs.radius + rhs.radius;
}

bool Intersect(ColliderCircle const& lhs, ColliderBox const& rhs) {
	return false; //TODO
}

bool Intersect(ColliderCircle const& lhs, ColliderPoint const& rhs) {
	return false; //TODO
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

bool Intersect(ColliderBox const& lhs, ColliderPoint const& rhs) {
	return false; //TODO
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