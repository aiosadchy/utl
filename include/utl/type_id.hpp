#ifndef UTL_TYPE_ID_HPP
#define UTL_TYPE_ID_HPP

#include "utl/type_traits.hpp"

namespace utl {

namespace init {

    enum class TypeID {
        LAZY,
        STATIC
    };

} // namespace init


template <
        typename TFamily,
        typename TIndex = unsigned short int,
        template <typename> typename TDecay = utl::type_traits::Identity,
        init::TypeID V_INIT_MODE = init::TypeID::LAZY
>
class TypeID {
public:
    using Family = TFamily;

    using Index = TIndex;

    template <typename T>
    using Decay = TDecay<T>;

    static constexpr init::TypeID INIT_MODE = V_INIT_MODE;

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
        if constexpr (type_traits::IS_SAME<T, Decay<T>>) {
            if constexpr (INIT_MODE == init::TypeID::LAZY) {
                static const Index type_index{s_registered_types++};
                return TypeID{type_index};
            } else {
                return TypeID{s_type_index<T>};
            }
        } else {
            return get<Decay<T>>();
        }
    }

    static Index get_types_count() {
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
