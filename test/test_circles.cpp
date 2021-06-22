#include "test_circles.hpp"

#include "colliders.hpp"

static TestResult expectOverlaps() {
	TestResult results;

	results.expected = 5;

	//circle-line
	{
		ColliderCircle circle {{0, 0}, 4};
		ColliderLine line {{-10, 4}, {10, 4}};

		if (Intersect(circle, line)) {
			results.observed++;
		}
	}

	//circle-circle
	{
		ColliderCircle a {{0, 0}, 5};
		ColliderCircle b {{0, 1}, 5};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//circle-circle edge case
	{
		ColliderCircle a {{0, 0}, 5};
		ColliderCircle b {{0, 10}, 5};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//circle-box
	{
		ColliderCircle circle {{0, 0}, 5};
		ColliderBox box {{5, 5}, {2.5, 2.5}};

		if (Intersect(circle, box)) {
			results.observed++;
		}
	}

	//circle-point
	{
		ColliderCircle circle {{0, 0}, 5};
		ColliderPoint point {{2, 2}};

		if (Intersect(circle, point)) {
			results.observed++;
		}
	}

	return results;
}

static TestResult expectNoOverlaps() {
	TestResult results;

	results.expected = 4;

	//circle-line
	{
		ColliderCircle circle {{0, 0}, 4};
		ColliderLine line {{-10, 4}, {10, 5}};

		if (!Intersect(circle, line)) {
			results.observed++;
		}
	}

	//circle-circle
	{
		ColliderCircle a {{0, 0}, 5};
		ColliderCircle b {{0, 20}, 5};

		if (!Intersect(a, b)) {
			results.observed++;
		}
	}

	//circle-box
	{
		ColliderCircle circle {{0, 0}, 5};
		ColliderBox box {{10, 10}, {2.5, 2.5}};

		if (!Intersect(circle, box)) {
			results.observed++;
		}
	}

	//circle-point
	{
		ColliderCircle circle {{0, 0}, 5};
		ColliderPoint point {{10, 10}};

		if (!Intersect(circle, point)) {
			results.observed++;
		}
	}

	return results;
}

TestResult testCircles() {
	return
		expectOverlaps() +
		expectNoOverlaps()
	;
}