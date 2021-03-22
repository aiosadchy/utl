#ifndef UTL_STATIC_BLOCK_HPP
#define UTL_STATIC_BLOCK_HPP

#include "utl/concatenate.hpp"

#define UTL_STATIC_BLOCK_IMPL(function, variable)                   \
    static void function();                                         \
    [[maybe_unused]] static const auto variable = (function(), 0);  \
    static void function()


#define UTL_STATIC_BLOCK                                    \
    UTL_STATIC_BLOCK_IMPL(                                  \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _function),  \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _variable)   \
    )


#ifndef UTL_NO_UNSCOPED_MACROS

    #define STATIC_BLOCK                                        \
        UTL_STATIC_BLOCK_IMPL(                                  \
            UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _function),  \
            UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _variable)   \
        )

#endif


#endif // UTL_STATIC_BLOCK_HPP
