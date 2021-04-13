#ifndef UTL_TYPE_TRAITS_HPP
#define UTL_TYPE_TRAITS_HPP

#include <type_traits>

namespace utl {

namespace type_traits {

namespace detail {

template <int I, typename First, typename... Rest>
class PackElement {
public:
    static_assert(I >= 0 && I <= sizeof...(Rest), "Type index out of range");
    using Type = typename PackElement<I - 1, Rest...>::Type;

};

template <typename First, typename... Rest>
class PackElement<0, First, Rest...> {
public:
    using Type = First;

};


template <typename T, template <typename...> typename Template>
class IsSpecialization : public std::false_type {};

template <template <typename...> typename Template, typename... Args>
class IsSpecialization<Template<Args...>, Template> : public std::true_type {};

} // namespace detail


template <typename T>
using Identity = T;

template <typename T>
using Decay = std::decay_t<T>;

template <typename... Types>
class Pack {
public:
    template <int I>
    using Element = typename detail::PackElement<I, Types...>::Type;

};


template <typename T, typename U>
constexpr bool IS_SAME = std::is_same_v<T, U>;

template <typename T, template <typename...> typename Template>
constexpr bool IS_SPECIALIZATION = detail::IsSpecialization<T, Template>::value;

} // namespace type_traits

} // namespace utl

#endif // UTL_TYPE_TRAITS_HPP
