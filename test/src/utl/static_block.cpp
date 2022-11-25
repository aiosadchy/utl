#include <utl/static_block.hpp>

#include "test.hpp"

static bool value_a = false;
static bool value_b = false;
static bool value_c = false;

UTL_STATIC_BLOCK {
    value_a = true;
}

UTL_STATIC_BLOCK {
    value_c = true;
}

TEST(static_block) {
    ASSERT(value_a == true)
    ASSERT(value_b == false)
    ASSERT(value_c == true)
}
