#include <utl/scope_guard.hpp>

#include "test.hpp"


static int scope_guard_target = 0;

static void scope_guard_callback() {
    scope_guard_target = 10;
}


TEST(scope_guard_class) {
    ASSERT(scope_guard_target == 0)
    utl::ScopeGuard guard = scope_guard_callback;
    ASSERT(scope_guard_target == 0)

    utl::ScopeGuard{[](){ scope_guard_target = 5; }};
    ASSERT(scope_guard_target == 5)

    {
        ASSERT(scope_guard_target == 5)
        utl::ScopeGuard local_guard = scope_guard_callback;
        ASSERT(scope_guard_target == 5)
    }

    ASSERT(scope_guard_target == 10)

}

TEST(scope_guard_macro) {
    int value = 0;

    UTL_SCOPE_GUARD {
        ASSERT(value == 5)
        value = 10;
    };
    ASSERT(value == 0)

    {
        ASSERT(value == 2)
        UTL_SCOPE_GUARD {
            value = 5;
        };
        ASSERT(value == 0)
    }

    ASSERT(value == 5)
}


TEST(scope_guard) {
    RUN_TEST(scope_guard_class)
    RUN_TEST(scope_guard_macro)
}
