#pragma once

#include "vector2.hpp"

class ColliderLine {
public:
	Vector2 center; //point A
	Vector2 projection; //point B
};

class ColliderCircle {
public:
	Vector2 center;
	double radius;
};

class ColliderBox {
public:
	Vector2 center;
	Vector2 halfSize;
};

class ColliderPoint {
public:
	Vector2 center;
};

//vector shifts and assignments
ColliderLine operator+(ColliderLine const& lhs, Vector2 const& rhs);
ColliderCircle operator+(ColliderCircle const& lhs, Vector2 const& rhs);
ColliderBox operator+(ColliderBox const& lhs, Vector2 const& rhs);
ColliderPoint operator+(ColliderPoint const& lhs, Vector2 const& rhs);

ColliderLine& operator+=(ColliderLine& lhs, Vector2 const& rhs);
ColliderCircle& operator+=(ColliderCircle& lhs, Vector2 const& rhs);
ColliderBox& operator+=(ColliderBox& lhs, Vector2 const& rhs);
ColliderPoint& operator+=(ColliderPoint& lhs, Vector2 const& rhs);

//intersection functions
bool Intersect(ColliderLine const& lhs, ColliderLine const& rhs);
bool Intersect(ColliderLine const& lhs, ColliderCircle const& rhs);
bool Intersect(ColliderLine const& lhs, ColliderBox const& rhs);
bool Intersect(ColliderLine const& lhs, ColliderPoint const& rhs);

bool Intersect(ColliderCircle const& lhs, ColliderLine const& rhs);
bool Intersect(ColliderCircle const& lhs, ColliderCircle const& rhs);
bool Intersect(ColliderCircle const& lhs, ColliderBox const& rhs);
bool Intersect(ColliderCircle const& lhs, ColliderPoint const& rhs);

bool Intersect(ColliderBox const& lhs, ColliderLine const& rhs);
bool Intersect(ColliderBox const& lhs, ColliderCircle const& rhs);
bool Intersect(ColliderBox const& lhs, ColliderBox const& rhs);
bool Intersect(ColliderBox const& lhs, ColliderPoint const& rhs);

bool Intersect(ColliderPoint const& lhs, ColliderLine const& rhs);
bool Intersect(ColliderPoint const& lhs, ColliderCircle const& rhs);
bool Intersect(ColliderPoint const& lhs, ColliderBox const& rhs);
bool Intersect(ColliderPoint const& lhs, ColliderPoint const& rhs);

