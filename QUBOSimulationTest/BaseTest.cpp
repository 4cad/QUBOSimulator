#include "pch.h"
#include "BaseTest.h"

#include "CPUBruteForceSolver.h"

void BaseTest::Expect(float objective, std::vector<int> variables) {
	expected_.objective = objective;
	expected_.variables = V(variables);

	CPUBruteForceSolver cpu_solver;

	Model* model = builder_.Build();
	Solution actual_ = cpu_solver.Solve(*model);

	EXPECT_EQ(expected_.objective, actual_.objective);
	EXPECT_EQ(expected_.variables, actual_.variables);
}