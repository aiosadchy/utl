#ifndef UTL_REPEAT_HPP
#define UTL_REPEAT_HPP

#include "utl/anonymous_identifier.hpp"
#include "utl/range.hpp"

#define UTL_REPEAT(count) \
    for ([[maybe_unused]] auto UTL_ANONYMOUS_IDENTIFIER : utl::Range(count))

#endif // UTL_REPEAT_HPP
