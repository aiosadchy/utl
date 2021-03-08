#ifndef UTL_NON_CONSTRUCTABLE_HPP
#define UTL_NON_CONSTRUCTABLE_HPP

#define UTL_NON_CONSTRUCTABLE(Type) \
    Type() = delete;                \
    ~Type() = delete;

#endif // UTL_NON_CONSTRUCTABLE_HPP
