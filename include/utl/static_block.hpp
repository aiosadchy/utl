#ifndef UTL_STATIC_BLOCK_HPP
#define UTL_STATIC_BLOCK_HPP

#include "utl/macro.hpp"

#define UTL_STATIC_BLOCK_IMPL(function, variable)                   \
    static void function();                                         \
    [[maybe_unused]] static const auto variable = (function(), 0);  \
    static void function()


#define STATIC_BLOCK UTL_STATIC_BLOCK_IMPL(         \
    CONCATENATE(ANONYMOUS_IDENTIFIER, _function),   \
    CONCATENATE(ANONYMOUS_IDENTIFIER, _variable)    \
)

#endif // UTL_STATIC_BLOCK_HPP
