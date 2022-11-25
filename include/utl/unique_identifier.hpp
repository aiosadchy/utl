#ifndef UTL_UNIQUE_IDENTIFIER_HPP
#define UTL_UNIQUE_IDENTIFIER_HPP

#include "utl/concatenate.hpp"

#if !defined(UTL_DO_NOT_USE_COUNTER_MACRO) && defined(__COUNTER__)
    #define UTL_DETAIL_COUNTER_MACRO __COUNTER__
#else
    #define UTL_DETAIL_COUNTER_MACRO __LINE__
#endif


#define UTL_UNIQUE_IDENTIFIER \
    UTL_CONCATENATE(utl_unique_identifier_, UTL_DETAIL_COUNTER_MACRO)

#ifndef UTL_NO_UNSCOPED_MACROS

#define UNIQUE_IDENTIFIER \
    UTL_CONCATENATE(utl_unique_identifier_, UTL_DETAIL_COUNTER_MACRO)

#endif

#endif // UTL_UNIQUE_IDENTIFIER_HPP
