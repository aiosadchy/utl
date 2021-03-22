#ifndef UTL_TYPE_TRAITS_HPP
#define UTL_TYPE_TRAITS_HPP

#include <type_traits>

namespace utl {

namespace type_traits {

namespace detail {

template <typename T, template <typename...> typename Template>
class IsSpecializationType : public std::false_type {};

template <template <typename...> typename Template, typename... Args>
class IsSpecializationType<Template<Args...>, Template> : public std::true_type {};

} // namespace detail


template <typename T>
using Identity = T;

template <typename T>
using Decay = std::decay_t<T>;

template <typename T, typename U>
constexpr bool is_same = std::is_same_v<T, U>;

template <typename T, template <typename...> typename Template>
constexpr bool IS_SPECIALIZATION = detail::IsSpecializationType<T, Template>::value;

} // namespace type_traits

} // namespace utl

#endif // UTL_TYPE_TRAITS_HPP
