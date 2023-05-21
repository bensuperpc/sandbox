#include <array>
#include <string>

#include "gtest/gtest.h"

#include "sandbox.hpp"

TEST(sandbox, basic1) {
    auto sandbox = benlib::sendbox(1024, 1024);
    //EXPECT_EQ("A", static_cast<std::string>(tmp1.data()));
}