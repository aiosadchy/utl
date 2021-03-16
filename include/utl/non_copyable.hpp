#ifndef UTL_NON_COPYABLE_HPP
#define UTL_NON_COPYABLE_HPP

#define UTL_NON_COPYABLE(Type)                      \
    Type(const Type &another) = delete;             \
    Type &operator=(const Type &another) = delete;


#ifdef UTL_UNSCOPED_MACROS

    #define NON_COPYABLE(Type)                          \
        Type(const Type &another) = delete;             \
        Type &operator=(const Type &another) = delete;

#endif

#endif // UTL_NON_COPYABLE_HPP
