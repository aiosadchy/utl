#ifndef UTL_UNIQUE_IDENTIFIER_HPP
#define UTL_UNIQUE_IDENTIFIER_HPP

#include "utl/concatenate.hpp"

#if defined(UTL_USE_COUNTER_MACRO) && defined(__COUNTER__)
    #define UTL_UNIQUE_IDENTIFIER \
        UTL_CONCATENATE(utl_unique_identifier_, __COUNTER__)
#else
    #define UTL_UNIQUE_IDENTIFIER \
        UTL_CONCATENATE(utl_unique_identifier_, __LINE__)
#endif


#ifdef UTL_UNSCOPED_MACROS

    #if defined(UTL_USE_COUNTER_MACRO) && defined(__COUNTER__)
        #define UNIQUE_IDENTIFIER \
            UTL_CONCATENATE(utl_unique_identifier_, __COUNTER__)
    #else
        #define UNIQUE_IDENTIFIER \
            UTL_CONCATENATE(utl_unique_identifier_, __LINE__)
    #endif

#endif

#endif // UTL_UNIQUE_IDENTIFIER_HPP
