#include <type_traits>

#include <utl/default_movable.hpp>

#include "test.hpp"

namespace {

class ExplicitlyMovable {
public:
    ExplicitlyMovable(ExplicitlyMovable &&) noexcept {
    }

    ExplicitlyMovable &operator=(ExplicitlyMovable &&) noexcept {
        return *this;
    }
};

class NonMovable {
public:
    ~NonMovable() {
    }

    ExplicitlyMovable m_property;
};

class Movable {
public:
    ~Movable() {
    }

    ExplicitlyMovable m_property;

    UTL_DEFAULT_MOVABLE(Movable)
};

} // namespace

TEST(default_copyable) {
    ASSERT(!std::is_move_constructible_v<NonMovable>)
    ASSERT(!std::is_move_assignable_v<NonMovable>)

    ASSERT(std::is_move_constructible_v<Movable>)
    ASSERT(std::is_move_assignable_v<Movable>)
}
