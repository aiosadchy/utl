#ifndef UTL_STORAGE_HPP
#define UTL_STORAGE_HPP

#include <type_traits>

namespace utl {

namespace detail {

template <typename T>
class Storage {
public:
    using Type = T;

    Type *ptr() {
        return reinterpret_cast<Type *>(m_data);
    }

    const Type *ptr() const {
        return reinterpret_cast<const Type *>(m_data);
    }

    Type &ref() {
        return *ptr();
    }

    const Type &ref() const {
        return *ptr();
    }

private:
    alignas(Type) unsigned char m_data[sizeof(Type)];

};

} // namespace detail


template <typename T>
using Storage = std::enable_if_t<
        (sizeof(T) == sizeof(detail::Storage<T>))
        && (alignof(T) == alignof(detail::Storage<T>)),
        detail::Storage<T>
>;

} // namespace utl

#endif // UTL_STORAGE_HPP
