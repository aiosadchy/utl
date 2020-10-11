#ifndef UTL_ANONYMOUS_IDENTIFIER_HPP
#define UTL_ANONYMOUS_IDENTIFIER_HPP

#include "utl/macro.hpp"

#if defined(UTL_DONT_USE_COUNTER_MACRO) || !defined(__COUNTER__)
    #define ANONYMOUS_IDENTIFIER CONCATENATE(_utl_anonymous_, __LINE__)
#else
    #define ANONYMOUS_IDENTIFIER CONCATENATE(_utl_anonymous_, __COUNTER__)
#endif

#endif // UTL_ANONYMOUS_IDENTIFIER_HPP
