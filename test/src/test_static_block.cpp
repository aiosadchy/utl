#include <utl/static_block.hpp>

#include "tests.hpp"


static bool value_a = false;
static bool value_b = false;

UTL_STATIC_BLOCK {
    value_a = true;
}

TEST(static_block) {
    ASSERT(value_a == true)
    ASSERT(value_b == false)
}
