#include <utl/repeat.hpp>

#include "tests.hpp"


TEST(repeat_regular) {
    int i = 0;
    UTL_REPEAT(10) {
        ++i;
    }
    ASSERT(i == 10)
}

TEST(repeat_zero_times) {
    bool value = true;
    UTL_REPEAT(0) {
        value = false;
    }
    ASSERT(value)
}

TEST(repeat_negative_counter) {
    bool value = true;
    UTL_REPEAT(-10) {
        value = false;
    }
    ASSERT(value)
}

TEST(repeat) {
    RUN_TEST(repeat_regular)
    RUN_TEST(repeat_zero_times)
    RUN_TEST(repeat_negative_counter)
}
