#ifndef UTL_STRING_LITERAL_HPP
#define UTL_STRING_LITERAL_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

namespace utl {

template <typename TCharacter, TCharacter... V_CHARACTERS>
class StringLiteral {
public:
    using Character = TCharacter;

public:
    static constexpr Character VALUE[sizeof...(V_CHARACTERS)] = {V_CHARACTERS...};
};

namespace detail {

template <typename TCharacter, TCharacter... V_CHARACTERS>
constexpr std::size_t string_literal_size() {
    constexpr TCharacter string[] = {V_CHARACTERS...};

    std::size_t size = 0;
    for (std::size_t i = 0; i < sizeof...(V_CHARACTERS); ++i) {
        if (string[i] != TCharacter{0}) {
            size = i + 1;
        }
    }
    return size + 1;
}

template <typename TCharacter, TCharacter... V_CHARACTERS, std::size_t... V_INDICES>
constexpr auto make_truncated_string_literal(std::index_sequence<V_INDICES...>) {
    constexpr TCharacter string[] = {V_CHARACTERS..., TCharacter{0}};
    return StringLiteral<TCharacter, string[V_INDICES]...>{};
}

template <typename TCharacter, TCharacter... V_CHARACTERS>
using TruncatedStringLiteral = decltype(
    make_truncated_string_literal<TCharacter, V_CHARACTERS...>(
        std::make_index_sequence<string_literal_size<TCharacter, V_CHARACTERS...>()>()
    )
);

} // namespace detail

} // namespace utl

// clang-format off

#define UTL_DETAIL_UNWRAP_STRING_1(string_literal, index) \
    ((index) < std::size(string_literal)                  \
         ? (string_literal)[index]                        \
         : std::decay_t<decltype(*(string_literal))>{0})

#define UTL_DETAIL_UNWRAP_STRING_4(string_literal, index)           \
    UTL_DETAIL_UNWRAP_STRING_1(string_literal, (index) + 1 * 0),    \
    UTL_DETAIL_UNWRAP_STRING_1(string_literal, (index) + 1 * 1),    \
    UTL_DETAIL_UNWRAP_STRING_1(string_literal, (index) + 1 * 2),    \
    UTL_DETAIL_UNWRAP_STRING_1(string_literal, (index) + 1 * 3)

#define UTL_DETAIL_UNWRAP_STRING_16(string_literal, index)          \
    UTL_DETAIL_UNWRAP_STRING_4(string_literal, (index) + 4 * 0),    \
    UTL_DETAIL_UNWRAP_STRING_4(string_literal, (index) + 4 * 1),    \
    UTL_DETAIL_UNWRAP_STRING_4(string_literal, (index) + 4 * 2),    \
    UTL_DETAIL_UNWRAP_STRING_4(string_literal, (index) + 4 * 3)

#define UTL_DETAIL_UNWRAP_STRING_64(string_literal, index)          \
    UTL_DETAIL_UNWRAP_STRING_16(string_literal, (index) + 16 * 0),  \
    UTL_DETAIL_UNWRAP_STRING_16(string_literal, (index) + 16 * 1),  \
    UTL_DETAIL_UNWRAP_STRING_16(string_literal, (index) + 16 * 2),  \
    UTL_DETAIL_UNWRAP_STRING_16(string_literal, (index) + 16 * 3)

// TODO: [maybe] add hash for longer strings
#define UTL_DETAIL_UNWRAP_STRING(string_literal)    \
    UTL_DETAIL_UNWRAP_STRING_64(string_literal, 0), \
    (std::decay_t<decltype(*(string_literal))>{0})

// clang-format on

#define UTL_STRING_LITERAL_CLASS(string_literal)   \
    utl::detail::TruncatedStringLiteral<           \
        std::decay_t<decltype(*(string_literal))>, \
        UTL_DETAIL_UNWRAP_STRING(string_literal)>

#ifndef UTL_NO_UNSCOPED_MACROS

#define STRING_LITERAL_CLASS(string_literal)       \
    utl::detail::TruncatedStringLiteral<           \
        std::decay_t<decltype(*(string_literal))>, \
        UTL_DETAIL_UNWRAP_STRING(string_literal)>

#endif

#endif // UTL_STRING_LITERAL_HPP
