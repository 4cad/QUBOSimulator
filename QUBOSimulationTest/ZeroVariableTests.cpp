#include "pch.h"

#include "BaseTest.h"


class ZeroVariableTests : public BaseTest {};

TEST_F(ZeroVariableTests, SampleTest) {
    Expect(0, {});
}
