//test headers
#include "test_compiles.hpp"
#include "test_lines.hpp"

#include "common.hpp"

#include <functional>
#include <iostream>
#include <vector>

const std::vector<std::function<TestResult()>> testVector = {
	testCompiles,
	testLines,
};

int main() {
	TestResult results;

	//run each test in sequence, recording the result
	for (auto t : testVector) {
		results += t();
	}

	//finally
	std::cout <<  results.observed << "/" << results.expected << " tests passed." << std::endl;
	return results.expected - results.observed;
}