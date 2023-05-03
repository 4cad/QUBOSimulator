#include "BaseTest.h"

class TwoVariableTests : public BaseTest {};

TEST_F(TwoVariableTests, NoQuadratic_BothPositive) {
    L(v0) = 10;
    L(v1) = 10;
    Expect(0, { 0, 0 });
}

TEST_F(TwoVariableTests, NoQuadratic_BothNegative) {
    L(v0) = -10;
    L(v1) = -10;
    Expect(-20, { 1, 1 });
}

TEST_F(TwoVariableTests, NoQuadratic_PosNeg) {
    L(v0) = 10;
    L(v1) = -10;
    Expect(-10, { 0, 1 });
}

TEST_F(TwoVariableTests, NoQuadratic_NegPos) {
    L(v0) = -10;
    L(v1) = 10;
    Expect(-10, { 1, 0 });
}

TEST_F(TwoVariableTests, NoLinear_Positive) {
    Q(v0, v1) = 10;
    Expect(0, { 0, 0 });
}

TEST_F(TwoVariableTests, NoLinear_Negative) {
    Q(v0, v1) = -10;
    Expect(-10, { 1, 1 });
}

TEST_F(TwoVariableTests, AllNegative) {
    L(v0) = -10;
    L(v1) = -10;
    Q(v0, v1) = -10;
    Expect(-30, { 1, 1 });
}

TEST_F(TwoVariableTests, NegativeQuadraticOutweightLinearTerms) {
    L(v0) = 10;
    L(v1) = 10;
    Q(v0, v1) = -30;
    Expect(-10, { 1, 1 });
}

TEST_F(TwoVariableTests, PositiveQuadraticOutweightLinearTerms) {
    L(v0) = -10;
    L(v1) = -11;
    Q(v0, v1) = 30;
    Expect(-11, { 0, 1 });
}