#ifndef UTL_STATIC_BLOCK_HPP
#define UTL_STATIC_BLOCK_HPP

#include "utl/concatenate.hpp"
#include "utl/unique_identifier.hpp"

#define UTL_DETAIL_STATIC_BLOCK(function, variable)                         \
    static void function();                                                 \
    [[maybe_unused]] static const auto variable = (function(), void(), 0);  \
    static void function()


#define UTL_STATIC_BLOCK                                    \
    UTL_DETAIL_STATIC_BLOCK(                                \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _function),  \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _variable)   \
    )


#ifndef UTL_NO_UNSCOPED_MACROS

#define STATIC_BLOCK                                        \
    UTL_DETAIL_STATIC_BLOCK(                                \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _function),  \
        UTL_CONCATENATE(UTL_UNIQUE_IDENTIFIER, _variable)   \
    )

#endif


#endif // UTL_STATIC_BLOCK_HPP
