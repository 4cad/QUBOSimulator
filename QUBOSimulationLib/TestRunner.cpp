#include "TestRunner.h"

#include "TestCases.h"

#include "CPUBruteForceSolver.h"

namespace QUBO {
	void RunAllTests() {
		std::list<TestCase> tests = GetAllTests();
		for (TestCase& test : tests) {
			CPUBruteForceSolver solver;
			Model* model = test.builder->Build();
			Solution actual = solver.Solve(*model);
		}
	}
}