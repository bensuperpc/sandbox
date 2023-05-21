#include <array>
#include <string>

#include "gtest/gtest.h"

#include "sandbox.hpp"

TEST(sandbox, basic1) {
    auto sandbox = benlib::sendbox(1024, 1024);
    sandbox.Update();

    EXPECT_EQ(1, sandbox.GetGenerations());
}