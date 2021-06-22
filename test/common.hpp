#pragma once

struct TestResult {
	int expected = 0;
	int observed = 0;
};

inline TestResult operator+(TestResult lhs, TestResult rhs) {
	return { lhs.expected + rhs.expected, lhs.observed + rhs.observed };
}

inline TestResult& operator+=(TestResult& lhs, TestResult rhs) {
	lhs = lhs + rhs;
	return lhs;
}