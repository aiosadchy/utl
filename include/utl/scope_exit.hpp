#ifndef UTL_SCOPE_EXIT_HPP
#define UTL_SCOPE_EXIT_HPP

#include <utl/anonymous_identifier.hpp>
#include <utl/detail/scope_exit.hpp>

#define SCOPE_EXIT detail::ScopeExit ANONYMOUS_IDENTIFIER = [&]()

#endif // UTL_SCOPE_EXIT_HPP
