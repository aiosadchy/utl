#include <utl/default_copyable.hpp>

#include <type_traits>

#include "test.hpp"


namespace {

class NonCopyable {
public:
    NonCopyable(NonCopyable &&) noexcept {}

};

class Copyable {
public:
    Copyable(Copyable &&) noexcept {}

    UTL_DEFAULT_COPYABLE(Copyable)

};

}

TEST(default_copyable) {
    ASSERT(!std::is_copy_constructible_v<NonCopyable>)
    ASSERT(!std::is_copy_assignable_v<NonCopyable>)

    ASSERT(std::is_copy_constructible_v<Copyable>)
    ASSERT(std::is_copy_assignable_v<Copyable>)
}
