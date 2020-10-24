#ifndef UTL_SCOPE_GUARD_HPP
#define UTL_SCOPE_GUARD_HPP

#include <utility>
#include "utl/unique_identifier.hpp"

#define UTL_SCOPE_GUARD \
    utl::ScopeGuard ANONYMOUS_IDENTIFIER = [&]()


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

#endif // UTL_SCOPE_GUARD_HPP
