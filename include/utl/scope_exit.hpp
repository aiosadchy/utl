#ifndef UTL_SCOPE_EXIT_HPP
#define UTL_SCOPE_EXIT_HPP

#include <utility>
#include "utl/unique_identifier.hpp"

#define UTL_SCOPE_EXIT \
    utl::detail::ScopeExit ANONYMOUS_IDENTIFIER = [&]()


namespace utl {

namespace detail {

template <typename F>
class ScopeExit {
public:
    ScopeExit(F &&f)
        : m_function{std::forward<F>(f)} {
    }

    ~ScopeExit() {
        m_function();
    }

private:
    std::remove_reference_t<F> m_function;

};

} // namespace detail

} // namespace utl

#endif // UTL_SCOPE_EXIT_HPP
