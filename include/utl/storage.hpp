#ifndef UTL_STORAGE_HPP
#define UTL_STORAGE_HPP

#include <type_traits>

namespace detail {
    template <typename T>
    class Storage {
    public:
        T *ptr() {
            return reinterpret_cast<T *>(m_data);
        }

        const T *ptr() const {
            return reinterpret_cast<const T *>(m_data);
        }

        T &ref() {
            return *ptr();
        }

        const T &ref() const {
            return *ptr();
        }

    private:
        alignas(T) unsigned char m_data[sizeof(T)];

    };

} // namespace detail


template <typename T>
using Storage = std::enable_if_t<
        (sizeof(T) == sizeof(detail::Storage<T>))
        && (alignof(T) == alignof(detail::Storage<T>)),
        detail::Storage<T>
>;

#endif // UTL_STORAGE_HPP
