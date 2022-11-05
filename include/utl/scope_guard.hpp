#ifndef UTL_SCOPE_GUARD_HPP
#define UTL_SCOPE_GUARD_HPP

#include <execution>
#include <type_traits>
#include <utility>

#include "utl/unique_identifier.hpp"

namespace utl {

template <bool V_TRIGGER_ON_SUCCESS, bool V_TRIGGER_ON_EXCEPTION, typename TFunction>
class ScopeGuard {
public:
    ScopeGuard(TFunction &&f)
        : m_function{std::forward<TFunction>(f)}
        , m_uncaught_exceptions{std::uncaught_exceptions()} {
    }

    ~ScopeGuard() noexcept(noexcept(m_function())) {
        bool success = std::uncaught_exceptions() == m_uncaught_exceptions;
        if ((TRIGGER_ON_SUCCESS && success) || (TRIGGER_ON_EXCEPTION && !success)) {
            m_function();
        }
    }

    static constexpr bool TRIGGER_ON_SUCCESS   = V_TRIGGER_ON_SUCCESS;
    static constexpr bool TRIGGER_ON_EXCEPTION = V_TRIGGER_ON_EXCEPTION;

private:
    std::decay_t<TFunction> m_function;
    int m_uncaught_exceptions;

};

template <typename TFunction>
class ScopeExit : public ScopeGuard<true, true, TFunction> {
public:
    ScopeExit(TFunction &&f)
        : ScopeGuard<true, true, TFunction>(std::forward<TFunction>(f)) {
    }
};

template <typename TFunction>
class ScopeSuccess : public ScopeGuard<true, false, TFunction> {
public:
    ScopeSuccess(TFunction &&f)
        : ScopeGuard<true, false, TFunction>(std::forward<TFunction>(f)) {
    }
};

template <typename TFunction>
class ScopeFail : public ScopeGuard<false, true, TFunction> {
public:
    ScopeFail(TFunction &&f)
        : ScopeGuard<false, true, TFunction>(std::forward<TFunction>(f)) {
    }
};

} // namespace utl


#define UTL_SCOPE_EXIT \
    [[maybe_unused]] utl::ScopeExit UTL_UNIQUE_IDENTIFIER = [&]()

#define UTL_SCOPE_SUCCESS \
    [[maybe_unused]] utl::ScopeSuccess UTL_UNIQUE_IDENTIFIER = [&]()

#define UTL_SCOPE_FAIL \
    [[maybe_unused]] utl::ScopeFail UTL_UNIQUE_IDENTIFIER = [&]()


#ifndef UTL_NO_UNSCOPED_MACROS

    #define SCOPE_EXIT \
        [[maybe_unused]] utl::ScopeExit UTL_UNIQUE_IDENTIFIER = [&]()

    #define SCOPE_SUCCESS \
        [[maybe_unused]] utl::ScopeSuccess UTL_UNIQUE_IDENTIFIER = [&]()

    #define SCOPE_FAIL \
        [[maybe_unused]] utl::ScopeFail UTL_UNIQUE_IDENTIFIER = [&]()

#endif

#endif // UTL_SCOPE_GUARD_HPP
