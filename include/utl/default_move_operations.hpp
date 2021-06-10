#ifndef UTL_DEFAULT_MOVE_OPERATIONS_HPP
#define UTL_DEFAULT_MOVE_OPERATIONS_HPP

#define UTL_DEFAULT_MOVE_OPERATIONS(Type)               \
    Type(Type &&another) noexcept = default;            \
    Type &operator=(Type &&another) noexcept = default;


#ifndef UTL_NO_UNSCOPED_MACROS

    #define DEFAULT_MOVE_OPERATIONS(Type)                   \
        Type(Type &&another) noexcept = default;            \
        Type &operator=(Type &&another) noexcept = default;

#endif

#endif // UTL_DEFAULT_MOVE_OPERATIONS_HPP
