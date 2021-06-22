#include "test_boxes.hpp"

#include "colliders.hpp"

static TestResult expectOverlaps() {
	TestResult results;

	results.expected = 7;

	//box-line
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderLine line {{0, 0}, {1, 1}};

		if (Intersect(box, line)) {
			results.observed++;
		}
	}

	//box-line corner case
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderLine line {{-10, 5}, {10, 5}};

		if (Intersect(box, line)) {
			results.observed++;
		}
	}

	//box-circle
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderCircle circle {{0, 0}, 1};

		if (Intersect(box, circle)) {
			results.observed++;
		}
	}

	//box-box
	{
		ColliderBox a {{0, 0}, {2.5, 2.5}};
		ColliderBox b {{0, 0}, {2.5, 2.5}};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//box-box corner case
	{
		ColliderBox a {{0, 0}, {2.5, 2.5}};
		ColliderBox b {{5, 5}, {2.5, 2.5}};

		if (Intersect(a, b)) {
			results.observed++;
		}
	}

	//box-point
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderPoint point {{0, 0}};

		if (Intersect(box, point)) {
			results.observed++;
		}
	}

	//box-point corner case
	{
		ColliderBox box {{5, 5}, {5, 5}};
		ColliderPoint point {{10, 10}};

		if (Intersect(box, point)) {
			results.observed++;
		}
	}

	return results;
}

static TestResult expectNoOverlaps() {
	TestResult results;

	results.expected = 4;

	//box-line
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderLine line {{20, 0}, {20, 1}};

		if (!Intersect(box, line)) {
			results.observed++;
		}
	}

	//box-circle
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderCircle circle {{10, 10}, 1};

		if (!Intersect(box, circle)) {
			results.observed++;
		}
	}

	//box-box
	{
		ColliderBox a {{0, 0}, {2.5, 2.5}};
		ColliderBox b {{20, 20}, {2.5, 2.5}};

		if (!Intersect(a, b)) {
			results.observed++;
		}
	}

	//box-point
	{
		ColliderBox box {{0, 0}, {5, 5}};
		ColliderPoint point {{10, 10}};

		if (!Intersect(box, point)) {
			results.observed++;
		}
	}

	return results;
}

TestResult testBoxes() {
	return
		expectOverlaps() +
		expectNoOverlaps()
	;
}