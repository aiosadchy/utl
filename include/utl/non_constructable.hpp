#ifndef UTL_NON_CONSTRUCTABLE_HPP
#define UTL_NON_CONSTRUCTABLE_HPP

#define UTL_NON_CONSTRUCTABLE(Type) \
    Type() = delete;                \
    ~Type() = delete;


#ifdef UTL_UNSCOPED_MACROS

    #define NON_CONSTRUCTABLE(Type) \
        Type() = delete;            \
        ~Type() = delete;

#endif

#endif // UTL_NON_CONSTRUCTABLE_HPP
