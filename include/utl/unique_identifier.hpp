#ifndef UTL_UNIQUE_IDENTIFIER_HPP
#define UTL_UNIQUE_IDENTIFIER_HPP

#include "utl/concatenate.hpp"

#if defined(UTL_DONT_USE_COUNTER_MACRO) || !defined(__COUNTER__)
    #define UTL_UNIQUE_IDENTIFIER \
        UTL_CONCATENATE(_utl_unique_identifier_, __LINE__)
#else
    #define UTL_UNIQUE_IDENTIFIER \
        UTL_CONCATENATE(_utl_unique_identifier_, __COUNTER__)
#endif

#endif // UTL_UNIQUE_IDENTIFIER_HPP
