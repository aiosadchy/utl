#include <utl/repeat.hpp>

#include "test.hpp"


TEST(regular) {
    int i = 0;
    UTL_REPEAT(10) {
        ++i;
    }
    ASSERT(i == 10)
}

TEST(zero_times) {
    bool value = true;
    UTL_REPEAT(0) {
        value = false;
    }
    ASSERT(value)
}

TEST(negative_counter) {
    bool value = true;
    UTL_REPEAT(-10) {
        value = false;
    }
    ASSERT(value)
}

RUN_ALL_TESTS
