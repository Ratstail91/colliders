#include "test_lines.hpp"

#include "colliders.hpp"

static TestResult expectOverlaps() {
	TestResult results;

	results.expected = 2;

	//line-line basic
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

	return results;
}

static TestResult expectNoOverlaps() {
	TestResult results;

	results.expected = 1;

	//basic line-line
	{
		ColliderLine a {{5, 5}, {10, 10}};
		ColliderLine b {{0, 5}, {5, 0}};

		if (!Intersect(a, b)) {
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