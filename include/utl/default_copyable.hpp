#ifndef UTL_DEFAULT_COPYABLE_HPP
#define UTL_DEFAULT_COPYABLE_HPP

#define UTL_DEFAULT_COPYABLE(Type)                  \
    Type(const Type &another)            = default; \
    Type &operator=(const Type &another) = default;


#ifndef UTL_NO_UNSCOPED_MACROS

#define DEFAULT_COPYABLE(Type)                      \
    Type(const Type &another)            = default; \
    Type &operator=(const Type &another) = default;

#endif

#endif // UTL_DEFAULT_COPYABLE_HPP
