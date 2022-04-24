#include <utl/hash.hpp>

#include "test.hpp"

TEST(hash) {
    // TODO: tests
    std::cout << utl::hash(1, 2u, 3l) << std::endl;
    std::cout << utl::hash(3l, 2u, 1) << std::endl;
    std::cout << utl::hash(2u, 1) << std::endl;
    std::cout << utl::hash(1, 2u) << std::endl;
}
