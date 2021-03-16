#ifndef UTL_REPEAT_HPP
#define UTL_REPEAT_HPP

#include "utl/range.hpp"
#include "utl/unique_identifier.hpp"

#define UTL_REPEAT(count) \
    for ([[maybe_unused]] auto UTL_UNIQUE_IDENTIFIER : utl::Range(count))


#ifdef UTL_UNSCOPED_MACROS

    #define REPEAT(count) \
        for ([[maybe_unused]] auto UTL_UNIQUE_IDENTIFIER : utl::Range(count))

#endif

#endif // UTL_REPEAT_HPP
