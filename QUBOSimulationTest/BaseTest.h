#pragma once
#include "ModelBuilder.h"

#include "gtest/gtest.h"
using namespace QUBO;

inline size_t V(const std::vector<int> args)
{
	size_t result = 0;
	size_t var_bit = 1;
	for (int variable_value : args) {
		if (variable_value != 0) {
			result |= var_bit;
		}
		var_bit <<= 1;
	}
	return result;
}

class BaseTest : public ::testing::Test{
public:
	BaseTest()
		: v0(0), v1(1), v2(2), v3(3), v4(4), v5(5)
	{}

	void Expect(float objective, std::vector<int> variables);

	float& Q(Variable var1, Variable var2) {
		return builder_.Q(var1, var2);
	}
	float& L(Variable var1) {
		return builder_.L(var1);
	}

protected:
	Variable v0, v1, v2, v3, v4, v5;
	ModelBuilder builder_;
	Solution expected_;
};