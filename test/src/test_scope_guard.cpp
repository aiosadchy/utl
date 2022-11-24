#include <utl/scope_guard.hpp>

#include <stdexcept>

#include "test.hpp"


namespace {

constexpr int UNCHANGED = 0;
constexpr int CHANGED_ONCE = 1;
constexpr int CHANGED_TWICE = 2;
constexpr int INVALID = -1;

} // namespace


TEST(scope_exit) {
    int regular_flow_value = UNCHANGED;
    int exception_flow_value = UNCHANGED;

    UTL_SCOPE_EXIT {
        ASSERT(regular_flow_value == CHANGED_ONCE)
        regular_flow_value = CHANGED_TWICE;
    };
    ASSERT(regular_flow_value == UNCHANGED)

    {
        ASSERT(regular_flow_value == UNCHANGED)
        UTL_SCOPE_EXIT {
            regular_flow_value = CHANGED_ONCE;
        };
        ASSERT(regular_flow_value == UNCHANGED)
    }

    try {
        UTL_SCOPE_EXIT {
            exception_flow_value = CHANGED_ONCE;
        };
        ASSERT(exception_flow_value == UNCHANGED)
        throw std::runtime_error{"an exception"};
    } catch (...) {
        // do nothing
    }
    ASSERT(exception_flow_value == CHANGED_ONCE)

    ASSERT(regular_flow_value == CHANGED_ONCE)
    ASSERT(exception_flow_value == CHANGED_ONCE)
}

TEST(scope_success) {
    int regular_flow_value = UNCHANGED;
    int exception_flow_value = UNCHANGED;

    UTL_SCOPE_SUCCESS {
        ASSERT(regular_flow_value == CHANGED_ONCE)
        regular_flow_value = CHANGED_TWICE;
    };
    ASSERT(regular_flow_value == UNCHANGED)

    {
        ASSERT(regular_flow_value == UNCHANGED)
        UTL_SCOPE_SUCCESS {
            regular_flow_value = CHANGED_ONCE;
        };
        ASSERT(regular_flow_value == UNCHANGED)
    }

    try {
        UTL_SCOPE_SUCCESS {
            ASSERT(exception_flow_value == INVALID)
            exception_flow_value = CHANGED_ONCE;
        };
        ASSERT(exception_flow_value == UNCHANGED)
        throw std::runtime_error{"an exception"};
    } catch (...) {
        // do nothing
    }
    ASSERT(exception_flow_value == UNCHANGED)

    ASSERT(regular_flow_value == CHANGED_ONCE)
    ASSERT(exception_flow_value == UNCHANGED)
}

TEST(scope_fail) {
    int regular_flow_value = UNCHANGED;
    int exception_flow_value = UNCHANGED;

    UTL_SCOPE_FAIL {
        ASSERT(regular_flow_value == INVALID)
        regular_flow_value = CHANGED_TWICE;
    };
    ASSERT(regular_flow_value == UNCHANGED)

    {
        ASSERT(regular_flow_value == UNCHANGED)
        UTL_SCOPE_FAIL {
            regular_flow_value = CHANGED_ONCE;
        };
        ASSERT(regular_flow_value == UNCHANGED)
    }

    try {
        UTL_SCOPE_FAIL {
            exception_flow_value = CHANGED_ONCE;
        };
        ASSERT(exception_flow_value == UNCHANGED)
        throw std::runtime_error{"an exception"};
    } catch (...) {
        ASSERT(exception_flow_value == CHANGED_ONCE)
    }

    ASSERT(regular_flow_value == UNCHANGED)
    ASSERT(exception_flow_value == CHANGED_ONCE)
}
