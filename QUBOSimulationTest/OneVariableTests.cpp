#include "pch.h"

#include "BaseTest.h"


class OneVariableTests : public BaseTest {};

TEST_F(OneVariableTests, AllZeroCoefficients) {
    // Sets the linear coefficient of variable 0 to 0. This is needed because the model will automatically ignore variables that don't
    // have any coefficients explicitly set
    L(v0) = 0;
    Expect(0, { 0 });
}

TEST_F(OneVariableTests, PositiveCoefficient) {
    L(v0) = 50;
    Expect(0, { 0 });
}

TEST_F(OneVariableTests, NegativeCoefficient) {
    L(v0) = -50;
    Expect(-50, { 1 });
}