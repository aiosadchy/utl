#ifndef UTL_MACRO_HPP
#define UTL_MACRO_HPP

#define EVAL(x) x

#define CONCATENATE_WITHOUT_EXPANSION(x, y) x ## y

#define CONCATENATE(x, y) CONCATENATE_WITHOUT_EXPANSION(x, y)

#define STRINGIFY(x) #x

#endif // UTL_MACRO_HPP
