#ifndef UTL_STORAGE_HPP
#define UTL_STORAGE_HPP

#include <type_traits>

namespace utl {

namespace detail {

template <typename TType>
class Storage {
public:
    using Type = TType;

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


template <typename TType>
using Storage = std::enable_if_t<
        (sizeof(TType) == sizeof(detail::Storage<TType>))
        && (alignof(TType) == alignof(detail::Storage<TType>)),
        detail::Storage<TType>
>;

} // namespace utl

#endif // UTL_STORAGE_HPP
