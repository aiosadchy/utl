#ifndef UTL_SCOPE_GUARD_HPP
#define UTL_SCOPE_GUARD_HPP

#include <utility>

#include "utl/type_traits.hpp"
#include "utl/unique_identifier.hpp"

namespace utl {

template <typename TFunction>
class ScopeGuard {
public:
    ScopeGuard(TFunction &&f)
        : m_function{std::forward<TFunction>(f)} {
    }

    ~ScopeGuard() {
        m_function();
    }

private:
    type_traits::Decay<TFunction> m_function;

};

} // namespace utl


#define UTL_SCOPE_GUARD \
    [[maybe_unused]] utl::ScopeGuard UTL_UNIQUE_IDENTIFIER = [&]()


#ifdef UTL_UNSCOPED_MACROS

    #define SCOPE_GUARD \
        [[maybe_unused]] utl::ScopeGuard UTL_UNIQUE_IDENTIFIER = [&]()

#endif

#endif // UTL_SCOPE_GUARD_HPP
