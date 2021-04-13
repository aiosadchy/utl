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

TEST(pack) {
    ASSERT(std::is_same_v<int,   utl::type_traits::Pack<int, float, bool>::Element<0>>)
    ASSERT(std::is_same_v<float, utl::type_traits::Pack<int, float, bool>::Element<1>>)
    ASSERT(std::is_same_v<bool,  utl::type_traits::Pack<int, float, bool>::Element<2>>)
}


namespace {

[[maybe_unused]] int function(char c, bool b) {
    return b ? 0 : static_cast<int>(c);
}

class C {
public:
    [[maybe_unused]] C *method(int x) {
        return this + x;
    }

    [[maybe_unused]] const C *const_method(int x) const {
        return this + x;
    }

};

} // namespace


TEST(function) {
    [[maybe_unused]] auto lambda = [](int &, float) {};
    using Lambda = decltype(lambda);
    ASSERT(std::is_same_v<void,  utl::type_traits::Function<Lambda>::Return>)
    ASSERT(std::is_same_v<int &, utl::type_traits::Function<Lambda>::Argument<0>>)
    ASSERT(std::is_same_v<float, utl::type_traits::Function<Lambda>::Argument<1>>)

    [[maybe_unused]] auto mutable_lambda = [](int &, float) mutable {};
    using MLambda = decltype(mutable_lambda);
    ASSERT(std::is_same_v<void,  utl::type_traits::Function<MLambda>::Return>)
    ASSERT(std::is_same_v<int &, utl::type_traits::Function<MLambda>::Argument<0>>)
    ASSERT(std::is_same_v<float, utl::type_traits::Function<MLambda>::Argument<1>>)

    [[maybe_unused]] auto constexpr_lambda = [](int &, float) constexpr {};
    using CLambda = decltype(constexpr_lambda);
    ASSERT(std::is_same_v<void,  utl::type_traits::Function<CLambda>::Return>)
    ASSERT(std::is_same_v<int &, utl::type_traits::Function<CLambda>::Argument<0>>)
    ASSERT(std::is_same_v<float, utl::type_traits::Function<CLambda>::Argument<1>>)

    using Function = decltype(function);
    ASSERT(std::is_same_v<int,  utl::type_traits::Function<Function>::Return>)
    ASSERT(std::is_same_v<char, utl::type_traits::Function<Function>::Argument<0>>)
    ASSERT(std::is_same_v<bool, utl::type_traits::Function<Function>::Argument<1>>)

    using PFunction = decltype(&function);
    ASSERT(std::is_same_v<int,  utl::type_traits::Function<PFunction>::Return>)
    ASSERT(std::is_same_v<char, utl::type_traits::Function<PFunction>::Argument<0>>)
    ASSERT(std::is_same_v<bool, utl::type_traits::Function<PFunction>::Argument<1>>)

    using Method = decltype(&C::method);
    ASSERT(std::is_same_v<C *, utl::type_traits::Function<Method>::Return>)
    ASSERT(std::is_same_v<int, utl::type_traits::Function<Method>::Argument<0>>)

    using CMethod = decltype(&C::const_method);
    ASSERT(std::is_same_v<const C *,  utl::type_traits::Function<CMethod>::Return>)
    ASSERT(std::is_same_v<int,        utl::type_traits::Function<CMethod>::Argument<0>>)
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
