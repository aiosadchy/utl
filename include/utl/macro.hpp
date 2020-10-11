#ifndef UTL_MACRO_HPP
#define UTL_MACRO_HPP

#define UTL_EVAL(x) \
    x

#define UTL_CONCATENATE_WITHOUT_EXPANSION(x, y) \
    x ## y

#define UTL_CONCATENATE(x, y) \
    UTL_CONCATENATE_WITHOUT_EXPANSION(x, y)

#define UTL_STRINGIFY(x) \
    #x

#endif // UTL_MACRO_HPP
