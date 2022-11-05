#include <utl/scope_guard.hpp>

#include "test.hpp"


static int scope_guard_target = 0;

static void scope_guard_callback() {
    scope_guard_target = 10;
}


TEST(scope_guard_class) {
    ASSERT(scope_guard_target == 0)
    utl::ScopeExit guard = scope_guard_callback;
    ASSERT(scope_guard_target == 0)

    utl::ScopeExit{[](){ scope_guard_target = 5; }};
    ASSERT(scope_guard_target == 5)

    {
        ASSERT(scope_guard_target == 5)
        utl::ScopeExit local_guard = scope_guard_callback;
        ASSERT(scope_guard_target == 5)
    }

    ASSERT(scope_guard_target == 10)

}

TEST(scope_guard_macro) {
    int value = 0;

    UTL_SCOPE_EXIT {
        ASSERT(value == 5)
        value = 10;
    };
    ASSERT(value == 0)

    {
        ASSERT(value == 0)
        UTL_SCOPE_EXIT {
            value = 5;
        };
        ASSERT(value == 0)
    }

    ASSERT(value == 5)
}

// TODO: test scope success and scope fail, test scope exit with exception
