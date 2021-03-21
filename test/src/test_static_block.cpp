#include <utl/static_block.hpp>

#include "test.hpp"


static bool value_a = false;
static bool value_b = false;

UTL_STATIC_BLOCK {
    value_a = true;
}

TEST(static_block) {
    ASSERT(value_a == true)
    ASSERT(value_b == false)
}

RUN_ALL_TESTS
