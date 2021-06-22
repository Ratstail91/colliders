#include "test_lines.hpp"

#include "colliders.hpp"

static TestResult expectOverlaps() {
	TestResult results;

	results.expected = 5;

	//line-line
	{
		ColliderLine a {{0, 0}, {1, 1}};
		ColliderLine b {{0, 1}, {1, 0}};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//line-line with a point in common
	{
		ColliderLine a {{0, 0}, {0, 1}};
		ColliderLine b {{0, 0}, {1, 0}};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//line-circle
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderCircle circle {{0, 1}, 5};

		if (Intersect(line, circle)) {
			results.observed++;
		}
	}

	//line-box
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderBox box {{0, 0}, {2.5, 2.5}};

		if (Intersect(line, box)) {
			results.observed++;
		}
	}

	//line-point
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderPoint point {{0, 0}};

		if (Intersect(line, point)) {
			results.observed++;
		}
	}

	return results;
}

static TestResult expectNoOverlaps() {
	TestResult results;

	results.expected = 4;

	//line-line
	{
		ColliderLine a {{5, 5}, {10, 10}};
		ColliderLine b {{0, 5}, {5, 0}};

		if (!Intersect(a, b)) {
			results.observed++;
		}
	}

	//line-circle
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderCircle circle {{0, 10}, 2};

		if (!Intersect(line, circle)) {
			results.observed++;
		}
	}

	//line-box
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderBox box {{20, 0}, {2.5, 2.5}};

		if (Intersect(line, box)) {
			results.observed++;
		}
	}

	//line-point
	{
		ColliderLine line {{-10, -10}, {10, 10}};
		ColliderPoint point {{1, 0}};

		if (Intersect(line, point)) {
			results.observed++;
		}
	}

	return results;
}

TestResult testLines() {
	return
		expectOverlaps() +
		expectNoOverlaps()
	;
}