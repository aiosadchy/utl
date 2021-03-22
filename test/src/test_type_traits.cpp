#include <utl/type_traits.hpp>

#include <map>
#include <type_traits>
#include <vector>

#include "test.hpp"


TEST(identity) {
    ASSERT(std::is_same_v<int, utl::type_traits::Identity<int>>)
    ASSERT(std::is_same_v<const int, utl::type_traits::Identity<const int>>)

    ASSERT(!std::is_same_v<int &, utl::type_traits::Identity<const int &>>)
    ASSERT(!std::is_same_v<int, utl::type_traits::Identity<double>>)
}

TEST(decay) {
    ASSERT(std::is_same_v<int, utl::type_traits::Decay<int>>)
    ASSERT(std::is_same_v<int, utl::type_traits::Decay<int &&>>)
    ASSERT(std::is_same_v<int, utl::type_traits::Decay<const int>>)
    ASSERT(std::is_same_v<int, utl::type_traits::Decay<const volatile int &>>)
}

TEST(is_same) {
    ASSERT(utl::type_traits::IS_SAME<int, int>)
    ASSERT(utl::type_traits::IS_SAME<const int &, const int &>)

    ASSERT(!utl::type_traits::IS_SAME<const int &, int>)
    ASSERT(!utl::type_traits::IS_SAME<float, int>)
}

TEST(is_specialization) {
    ASSERT(utl::type_traits::IS_SPECIALIZATION<std::vector<int>, std::vector>)
    ASSERT(utl::type_traits::IS_SPECIALIZATION<std::map<char, float>, std::map>)

    ASSERT(!utl::type_traits::IS_SPECIALIZATION<std::map<char, float>, std::vector>)
    ASSERT(!utl::type_traits::IS_SPECIALIZATION<std::vector<char>, std::map>)
}

TEST_MAIN
