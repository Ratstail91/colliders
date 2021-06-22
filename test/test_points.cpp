#include "test_points.hpp"

#include "colliders.hpp"

static TestResult expectOverlaps() {
	TestResult results;

	results.expected = 6;

	//point-line
	{
		ColliderPoint point {{0, 0}};
		ColliderLine line {{0, -5}, {0, 5}};

		if (Intersect(point, line)) {
			results.observed++;
		}
	}

	//point-circle
	{
		ColliderPoint point {{0, 0}};
		ColliderCircle circle {{0, 0}, 5};

		if (Intersect(point, circle)) {
			results.observed++;
		}
	}

	//point-circle corner case
	{
		ColliderPoint point {{5, 0}};
		ColliderCircle circle {{0, 0}, 5};

		if (Intersect(point, circle)) {
			results.observed++;
		}
	}

	//point-box
	{
		ColliderPoint point {{0, 0}};
		ColliderBox box {{0, 0}, {5, 5}};

		if (Intersect(point, box)) {
			results.observed++;
		}
	}

	//point-box corner case
	{
		ColliderPoint point {{5, 5}};
		ColliderBox box {{0, 0}, {5, 5}};

		if (Intersect(point, box)) {
			results.observed++;
		}
	}

	//point-point
	{
		ColliderPoint a {{0, 0}};
		ColliderPoint b {{0, 0}};

		if (Intersect(a, a)) {
			results.observed++;
		}
	}

	return results;
}

static TestResult expectNoOverlaps() {
	TestResult results;

	results.expected = 4;

	//point-line
	{
		ColliderPoint point {{0, 0}};
		ColliderLine line {{0, -5}, {1, 5}};

		if (!Intersect(point, line)) {
			results.observed++;
		}
	}

	//point-circle
	{
		ColliderPoint point {{0, 0}};
		ColliderCircle circle {{0, 10}, 5};

		if (!Intersect(point, circle)) {
			results.observed++;
		}
	}

	//point-box
	{
		ColliderPoint point {{0, 0}};
		ColliderBox box {{0, 10}, {5, 5}};

		if (!Intersect(point, box)) {
			results.observed++;
		}
	}

	//point-point
	{
		ColliderPoint a {{0, 0}};
		ColliderPoint b {{0, 1}};

		if (!Intersect(a, b)) {
			results.observed++;
		}
	}

	return results;
}

TestResult testPoints() {
	return
		expectOverlaps() +
		expectNoOverlaps()
	;
}