#ifndef UTL_TYPE_ID_HPP
#define UTL_TYPE_ID_HPP

#include "utl/type_traits.hpp"

namespace utl {

template <
        typename TFamily,
        typename TIndex = unsigned short int,
        bool LAZY_INITIALIZATION = true,
        template <typename> typename TDecay = type_traits::Identity
>
class TypeID {
public:
    using Family = TFamily;
    using Index = TIndex;

    TypeID()
        : m_index(Index{0} - Index{1}) {
    }

    Index get_index() const {
        return m_index;
    }

    bool operator==(const TypeID &another) const {
        return m_index == another.m_index;
    }

    bool operator!=(const TypeID &another) const {
        return m_index != another.m_index;
    }

    template <typename T>
    static TypeID get() {
        if constexpr (type_traits::is_same<T, TDecay<T>>) {
            if constexpr (LAZY_INITIALIZATION) {
                static const Index type_index{s_registered_types++};
                return TypeID{type_index};
            } else {
                return TypeID{s_type_index < T > };
            }
        } else {
            return get<TDecay<T>>();
        }
    }

    static Index get_registered_types_count() {
        return s_registered_types;
    }

private:
    explicit TypeID(Index index)
        : m_index{index} {
    }

    Index m_index;

    inline static Index s_registered_types{0};

    template <typename T>
    inline static const Index s_type_index{s_registered_types++};

};

} // namespace utl

#endif // UTL_TYPE_ID_HPP
