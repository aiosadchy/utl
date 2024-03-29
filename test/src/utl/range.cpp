#include <vector>

#include <utl/range.hpp>

#include "test.hpp"

template <typename T>
std::vector<T> vec(const utl::Range<T> &range) {
    std::vector<T> result;
    for (auto i : range) {
        result.push_back(i);
    }
    return result;
}

TEST(regular) {
    ASSERT(vec(utl::range(5)) == std::vector{0, 1, 2, 3, 4});
    ASSERT(vec(utl::range(7, 10)) == std::vector{7, 8, 9});
    ASSERT(vec(utl::range(0, 6, 2)) == std::vector{0, 2, 4});
    ASSERT(vec(utl::range(0, 7, 2)) == std::vector{0, 2, 4, 6});
}

TEST(empty) {
    ASSERT(vec(utl::range(0)).empty())
    ASSERT(vec(utl::range(7, 2)).empty())
    ASSERT(vec(utl::range(0, 6, -2)).empty())
    ASSERT(vec(utl::range(9, 3)).empty())
}

TEST(non_integral) {
    ASSERT(vec(utl::range(8.5)).size() == 9)
    ASSERT(vec(utl::range(2.3f, 1.95f, -0.1f)).size() == 4)
}

TEST(zero_step) {
    ASSERT(vec(utl::range(10, 20, 0)).empty())
    ASSERT(vec(utl::range(10, 5, 0)).empty())
    ASSERT(vec(utl::range(1.0, 2.0, 0.0)).empty())
}
