#ifndef UTL_SCOPE_GUARD_HPP
#define UTL_SCOPE_GUARD_HPP

#include <utility>
#include "utl/unique_identifier.hpp"

namespace utl {

template <typename F>
class ScopeGuard {
public:
    ScopeGuard(F &&f)
        : m_function{std::forward<F>(f)} {
    }

    ~ScopeGuard() {
        m_function();
    }

private:
    std::remove_reference_t<F> m_function;

};

} // namespace utl


#define UTL_SCOPE_GUARD \
    utl::ScopeGuard UTL_UNIQUE_IDENTIFIER = [&]()


#ifdef UTL_UNSCOPED_MACROS

    #define SCOPE_GUARD \
        utl::ScopeGuard UTL_UNIQUE_IDENTIFIER = [&]()

#endif

#endif // UTL_SCOPE_GUARD_HPP
