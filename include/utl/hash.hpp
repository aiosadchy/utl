#ifndef UTL_HASH_HPP
#define UTL_HASH_HPP

#include <functional>
#include <type_traits>
#include <iostream>

#include "utl/default_copyable.hpp"

namespace utl {

class Hash {
public:
    Hash()
        : m_hash_value{} {
    }

    UTL_DEFAULT_COPYABLE(Hash)

    template <typename T, typename THash = std::hash<T>>
    explicit Hash(const T &object, THash &&hash_function = THash{})
        : m_hash_value{hash_function(object)} {
        std::cout << "hashing " << object << std::endl;
    }

    [[nodiscard]] operator std::size_t() const {
        return m_hash_value;
    }

    [[nodiscard]] Hash operator^(const Hash &another) const {
        Hash result = *this;
        result.m_hash_value ^= another.m_hash_value
                             + std::size_t{0x9e3779b9}
                             + (result.m_hash_value << std::size_t{6})
                             + (result.m_hash_value >> std::size_t{2});
        return result;
    }

private:
    std::size_t m_hash_value;

};

template <typename... Args>
auto hash(Args &&...args) {
    return (Hash{args} ^ ...);
}

} // namespace utl

#endif // UTL_HASH_HPP
