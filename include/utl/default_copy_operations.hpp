#ifndef UTL_DEFAULT_COPY_OPERATIONS_HPP
#define UTL_DEFAULT_COPY_OPERATIONS_HPP

#define UTL_DEFAULT_COPY_OPERATIONS(Type)           \
    Type(const Type &another) = default;            \
    Type &operator=(const Type &another) = default;


#ifndef UTL_NO_UNSCOPED_MACROS

    #define DEFAULT_COPY_OPERATIONS(Type)               \
        Type(const Type &another) = default;            \
        Type &operator=(const Type &another) = default;

#endif

#endif // UTL_DEFAULT_COPY_OPERATIONS_HPP
