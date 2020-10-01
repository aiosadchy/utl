#ifndef UTL_DETAIL_SCOPE_EXIT_HPP
#define UTL_DETAIL_SCOPE_EXIT_HPP

#include <utility>

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

#endif // UTL_DETAIL_SCOPE_EXIT_HPP
