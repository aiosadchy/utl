#include <utl/range.hpp>

#include <vector>

#include "tests.hpp"


using namespace utl;

template <typename T>
std::vector<T> vec(const Range<T> &range) {
    std::vector<T> result;
    for (auto i : range) {
        result.push_back(i);
    }
    return result;
}

TEST(range_regular) {
    ASSERT(vec(Range(5)       ) == std::vector{0, 1, 2, 3, 4})
    ASSERT(vec(Range(7, 10)   ) == std::vector{7, 8, 9}      )
    ASSERT(vec(Range(0,  6, 2)) == std::vector{0, 2, 4}      )
    ASSERT(vec(Range(0,  7, 2)) == std::vector{0, 2, 4, 6}   )
}

TEST(range_empty) {
    ASSERT(vec(Range(0)       ).empty())
    ASSERT(vec(Range(7, 2)    ).empty())
    ASSERT(vec(Range(0, 6, -2)).empty())
    ASSERT(vec(Range(9, 3)    ).empty())
}

TEST(range_float) {
    ASSERT(vec(Range(8.5)            ).size() == 9)
    ASSERT(vec(Range(2.3, 1.95, -0.1)).size() == 4)
}

TEST(range_zero_step) {
    ASSERT(vec(Range( 10,  20,   0)).empty())
    ASSERT(vec(Range( 10,   5,   0)).empty())
    ASSERT(vec(Range(1.0, 2.0, 0.0)).empty())
}

TEST(range) {
    RUN_TEST(range_regular)
    RUN_TEST(range_empty)
    RUN_TEST(range_float)
    RUN_TEST(range_zero_step)
}
