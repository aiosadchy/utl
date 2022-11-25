#ifndef UTL_NON_CONSTRUCTIBLE_HPP
#define UTL_NON_CONSTRUCTIBLE_HPP

#define UTL_NON_CONSTRUCTIBLE(Type) \
    Type()  = delete;               \
    ~Type() = delete;


#ifndef UTL_NO_UNSCOPED_MACROS

#define NON_CONSTRUCTIBLE(Type) \
    Type()  = delete;           \
    ~Type() = delete;

#endif

#endif // UTL_NON_CONSTRUCTIBLE_HPP
