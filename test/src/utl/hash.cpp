#include <algorithm>
#include <numeric>
#include <type_traits>
#include <vector>

#include <utl/hash.hpp>

#include "test.hpp"

namespace {

std::size_t test_sample_count = 4096;

} // namespace

template <typename TInput, typename THashFunction>
void test_integer_hash(
    THashFunction hash_function,
    std::size_t   sample_count,
    TInput        start_value,
    double        tolerance
) {
    using Hash = std::invoke_result_t<THashFunction, TInput>;

    std::vector<TInput> values{};
    values.resize(sample_count);
    std::iota(values.begin(), values.end(), start_value);

    std::vector<Hash> hashes{};

    for (TInput x : values) {
        hashes.emplace_back(hash_function(x));
    }

    std::sort(hashes.begin(), hashes.end());
    hashes.erase(
        std::unique(hashes.begin(), hashes.end()),
        hashes.end()
    );

    ASSERT(sample_count - hashes.size() < sample_count * tolerance)
}

TEST(integer_hash32_unsigned) {
    test_integer_hash<std::uint32_t>(
        utl::integer_hash::hash32,
        test_sample_count,
        0,
        0.01
    );
}

TEST(integer_hash32_signed) {
    test_integer_hash<std::int32_t>(
        utl::integer_hash::hash32,
        test_sample_count,
        -test_sample_count / 2,
        0.01
    );
}

TEST(integer_hash64_unsigned) {
    test_integer_hash<std::int64_t>(
        utl::integer_hash::hash64,
        test_sample_count,
        -test_sample_count / 2,
        0.01
    );
}

TEST(integer_hash64_signed) {
    test_integer_hash<std::int64_t>(
        utl::integer_hash::hash64,
        test_sample_count,
        -test_sample_count / 2,
        0.01
    );
}

TEST(hash) {
    ASSERT(utl::hash(1) != utl::hash(2))
    ASSERT(utl::hash(1) != utl::hash(0, 1))
    ASSERT(utl::hash(0, 1) != utl::hash(1, 0))

    std::string        s1 = "s1";
    const std::string &s2 = "s2";

    ASSERT(utl::hash("s1") != utl::hash(s1))
    ASSERT(utl::hash(s1) != utl::hash(s2))
    ASSERT(utl::hash(std::string{"s1"}) == utl::hash(s1))
    ASSERT(utl::hash(s1) != utl::hash(1u, s1, "s1"))
}
