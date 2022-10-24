#ifndef UTL_HASH_HPP
#define UTL_HASH_HPP

#include <functional>
#include <type_traits>

#include "utl/default_copyable.hpp"

namespace utl {

class Hash {
public:
    UTL_DEFAULT_COPYABLE(Hash)

    template <typename T, typename THash = std::hash<T>>
    explicit Hash(const T &object, THash &&hash_function = THash{})
        : m_hash_value{hash_function(object)} {
    }

    [[nodiscard]] operator std::size_t() const {
        return m_hash_value;
    }

    Hash &operator^=(const Hash &another) {
        m_hash_value ^= another.m_hash_value
            + std::size_t{0x9e3779b9}
            + (m_hash_value << std::size_t{6})
            + (m_hash_value >> std::size_t{2});
        return *this;
    }

    [[nodiscard]] Hash operator^(const Hash &another) const {
        Hash result = *this;
        result ^= another;
        return result;
    }

    template <typename T>
    Hash &operator<<(const T &object) {
        *this ^= Hash{object};
        return *this;
    }

private:
    std::size_t m_hash_value;

};

template <typename... Args>
std::size_t hash(Args &&...args) {
    return (... ^ Hash{args});
}

} // namespace utl

#endif // UTL_HASH_HPP
