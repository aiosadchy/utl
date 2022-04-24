#ifndef UTL_HASH_HPP
#define UTL_HASH_HPP

#include <functional>

namespace utl {

class HashCombine {
public:
    template <typename First, typename... Rest>
    auto operator()(const First &first, const Rest &...rest) {
        if constexpr (sizeof...(Rest) == 0) {
            return first;
        } else {
            auto tail = (*this)(rest...);
            // boost::hash_combine
            return first ^ (tail + First{0x9e3779b9} + (first << First{6}) + (first >> First{2}));
        }
    }

};


template <typename T>
using Hash = std::hash<T>;


template <
    template <typename> typename THash = Hash,
    typename THashCombine = HashCombine,
    typename... Args
>
auto hash(Args &&...args) {
    return THashCombine{}(THash<Args>{}(args)...);
}

} // namespace utl

#endif // UTL_HASH_HPP
