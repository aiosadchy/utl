#ifndef UTL_HASH_HPP
#define UTL_HASH_HPP

#include <cstdint>
#include <functional>
#include <type_traits>

namespace utl {

namespace integer_hash {

// Credits: Hash Function Prospector contributors
// https://github.com/skeeto/hash-prospector
constexpr std::uint32_t hash32(std::uint32_t x) {
    x ^= x >> UINT32_C(16);
    x *= UINT32_C(0x21f0aaad);
    x ^= x >> UINT32_C(15);
    x *= UINT32_C(0x735a2d97);
    x ^= x >> UINT32_C(15);
    return x;
}

// Credits: Sebastiano Vigna (vigna@acm.org)
// https://xorshift.di.unimi.it/splitmix64.c
constexpr std::uint64_t hash64(std::uint64_t x) {
    x = (x ^ (x >> UINT64_C(30))) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> UINT64_C(27))) * UINT64_C(0x94d049bb133111eb);
    x = (x ^ (x >> UINT64_C(31)));
    return x;
}

} // namespace integer_hash

template <
    template <typename> typename THash = std::hash,
    typename TFirst,
    typename... TRest>
constexpr std::size_t hash(TFirst &&first, TRest &&...rest) {
    std::size_t result = THash<std::decay_t<TFirst>>{}(std::forward<TFirst>(first));
    if constexpr (sizeof...(TRest) > 0) {
        result ^= hash<THash>(std::forward<TRest>(rest)...)
                + std::size_t{UINTMAX_C(0x9e3779b9)}
                + (result << std::size_t{6})
                + (result >> std::size_t{2});
    }
    return result;
}

} // namespace utl

#endif // UTL_HASH_HPP
