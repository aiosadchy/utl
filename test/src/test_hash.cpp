#include <utl/hash.hpp>

#include "test.hpp"

std::size_t add_one(int x) {
    return static_cast<std::size_t>(x + 1);
}

TEST(hash) {
    // TODO: tests
    std::cout << utl::hash(1, 2u, 3l) << std::endl;
    std::cout << utl::hash(3l, 2u, 1) << std::endl;
    std::cout << utl::hash(2u, 1) << std::endl;
    std::cout << utl::hash(1, 2u) << std::endl;

    std::cout << utl::Hash(1, add_one) << std::endl;
}
