#ifndef UTL_TYPE_TRAITS_HPP
#define UTL_TYPE_TRAITS_HPP

#include <type_traits>

namespace utl {

namespace type_traits {

template <typename T>
using Identity = T;

template <typename T>
using Decay = std::decay_t<T>;

template <typename T, typename U>
constexpr bool is_same = std::is_same_v<T, U>;

}

} // namespace utl

#endif // UTL_TYPE_TRAITS_HPP
