#ifndef UTL_TYPE_TRAITS_HPP
#define UTL_TYPE_TRAITS_HPP

#include <type_traits>

namespace utl {

namespace type_traits {

namespace detail {

template <int I, typename... Types>
struct PackElement;

template <int I, typename First, typename... Rest>
struct PackElement<I, First, Rest...> {
    static_assert(I >= 0 && I <= sizeof...(Rest), "Type index out of range");
    using Type = typename PackElement<I - 1, Rest...>::Type;

};

template <typename First, typename... Rest>
struct PackElement<0, First, Rest...> {
    using Type = First;

};


template <typename T, template <typename...> typename Template>
struct IsSpecialization : std::false_type {};

template <template <typename...> typename Template, typename... Args>
struct IsSpecialization<Template<Args...>, Template> : std::true_type {};

} // namespace detail


template <typename T>
using Identity = T;

template <typename... Types>
struct Pack {
    template <int I>
    using Element = typename detail::PackElement<I, Types...>::Type;

    static constexpr int SIZE = sizeof...(Types);

};


template <typename F>
struct Function : Function<decltype(&F::operator())> {};

template <typename R, typename... Args>
struct Function<R (*)(Args...)> {
    using Return = R;

    template <int I>
    using Argument = typename Pack<Args...>::template Element<I>;

    static constexpr int ARGUMENTS_COUNT = Pack<Args...>::SIZE;

};

template <typename R, typename... Args>
struct Function<R (Args...)> : Function<R (*)(Args...)> {};

template <typename F, typename R, typename... Args>
struct Function<R (F::*)(Args...)> {
    using Return = R;

    template <int I>
    using Argument = typename Pack<Args...>::template Element<I>;

    static constexpr int ARGUMENTS_COUNT = Pack<Args...>::SIZE;

};

template <typename F, typename R, typename... Args>
struct Function<R (F::*)(Args...) const> : Function<R (F::*)(Args...)> {};


template <typename T, typename U>
constexpr bool IS_SAME = std::is_same_v<T, U>;

template <typename T, template <typename...> typename Template>
constexpr bool IS_SPECIALIZATION = detail::IsSpecialization<T, Template>::value;

} // namespace type_traits

} // namespace utl

#endif // UTL_TYPE_TRAITS_HPP
