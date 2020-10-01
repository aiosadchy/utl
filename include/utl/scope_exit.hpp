#ifndef UTL_SCOPE_EXIT_HPP
#define UTL_SCOPE_EXIT_HPP

#include <utility>
#include <utl/anonymous_identifier.hpp>

#define SCOPE_EXIT detail::ScopeExit ANONYMOUS_IDENTIFIER = [&]()


namespace detail {
    template <typename F>
    class ScopeExit {
    public:
        ScopeExit(F &&f)
                : m_function(std::forward<F>(f)) {
        }

        ~ScopeExit() {
            m_function();
        }

    private:
        F m_function;

    };

} // namespace detail

#endif // UTL_SCOPE_EXIT_HPP
