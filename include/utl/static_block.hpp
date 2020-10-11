#ifndef UTL_STATIC_BLOCK_HPP
#define UTL_STATIC_BLOCK_HPP

#include "utl/macro.hpp"

#define _UTL_STATIC_BLOCK_IMPL(function, variable)                  \
    static void function();                                         \
    [[maybe_unused]] static const auto variable = (function(), 0);  \
    static void function()


#define UTL_STATIC_BLOCK                                        \
    _UTL_STATIC_BLOCK_IMPL(                                     \
        UTL_CONCATENATE(UTL_ANONYMOUS_IDENTIFIER, _function),   \
        UTL_CONCATENATE(UTL_ANONYMOUS_IDENTIFIER, _variable)    \
    )

#endif // UTL_STATIC_BLOCK_HPP
