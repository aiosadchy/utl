#include <utl/string_literal_template.hpp>

#include <iterator>
#include <type_traits>

#include "test.hpp"


TEST(string_literal_template) {
    auto v1 = utl::StringLiteral<char, 'a', 'b', 'c', '\0'>{};
    auto v2 = UTL_STRING_LITERAL_TYPE("abc"){};

    ASSERT(std::is_same_v<decltype(v1), decltype(v2)>)
    ASSERT(std::string_view(v1.VALUE) == "abc")
    ASSERT(std::string_view(v2.VALUE) == "abc")


    using T3 = UTL_STRING_LITERAL_TYPE(L"abcd");

    ASSERT(!std::is_same_v<std::decay_t<decltype(v2)>, T3>)
    ASSERT(std::wstring_view(T3::VALUE) == L"abcd")


    using T0 = UTL_STRING_LITERAL_TYPE("");

    ASSERT(std::size(T0::VALUE) == 1)

    using TEmpty = utl::StringLiteral<char>;

    ASSERT(!std::is_same_v<T0, TEmpty>)

}
