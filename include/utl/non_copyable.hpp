#ifndef UTL_NON_COPYABLE_HPP
#define UTL_NON_COPYABLE_HPP

#define UTL_NON_COPYABLE(Type)                      \
    Type(const Type &another) = delete;             \
    Type &operator=(const Type &another) = delete;

#endif // UTL_NON_COPYABLE_HPP
