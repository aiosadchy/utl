#include <utl/non_constructible.hpp>

#include <type_traits>

#include "test.hpp"

namespace {

class Constructible {

};

class NonConstructible {
    UTL_NON_CONSTRUCTIBLE(NonConstructible)

};

} // namespace

TEST(non_constructible) {
    ASSERT(std::is_default_constructible_v<Constructible>)
    ASSERT(std::is_copy_constructible_v<Constructible>)
    ASSERT(std::is_move_constructible_v<Constructible>)

    ASSERT(!std::is_default_constructible_v<NonConstructible>)
    ASSERT(!std::is_copy_constructible_v<NonConstructible>)
    ASSERT(!std::is_move_constructible_v<NonConstructible>)
}
