#include "TestCases.h"

namespace QUBO {
	/*
	TestCase TwoVar_QuadOnly_BothOne() {
		TestCase t;
		ModelBuilder& b = *(t.builder);

		Variable v0(0);
		Variable v1(1);
		b.Q(v0, v1) = -50;

		t.expected_objective = -50;
		t.expected_solution = V({ 1, 1 });
		return t;
	}

	TestCase TwoVar_QuadOnly_BothZero() {
		TestCase t;
		ModelBuilder& b = *(t.builder);

		Variable v0(0);
		Variable v1(1);
		b.Q(v0, v1) = 50;

		t.expected_objective = 0;
		t.expected_solution = V({ 0, 0 });
		return t;
	}

	std::list<TestCase> GetAllTests() {
		std::list<TestCase> result;
		result.push_back(TwoVar_QuadOnly_BothOne());
		result.push_back(TwoVar_QuadOnly_BothZero());
		return result;
	}
	*/
	std::list<TestCase> GetAllTests() {
		return std::list<TestCase>();
	}
}