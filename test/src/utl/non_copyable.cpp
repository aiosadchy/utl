#include <type_traits>

#include <utl/non_copyable.hpp>

#include "test.hpp"

namespace {

class Copyable {
};

class NonCopyable {
    UTL_NON_COPYABLE(NonCopyable)
};

} // namespace

TEST(non_copyable) {
    ASSERT(std::is_copy_constructible_v<Copyable>)
    ASSERT(std::is_copy_assignable_v<Copyable>)

    ASSERT(!std::is_copy_constructible_v<NonCopyable>)
    ASSERT(!std::is_copy_assignable_v<NonCopyable>)
}
