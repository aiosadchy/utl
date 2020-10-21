#ifndef UTL_TYPE_ID_HPP
#define UTL_TYPE_ID_HPP

namespace utl {

template <
        typename TFamily,
        typename TIndex = unsigned short int,
        bool LAZY_INITIALIZATION = false
>
class TypeID {
public:
    using Family = TFamily;
    using Index = TIndex;

    TypeID()
        : m_index(Index(0) - Index(1)) {
    }

    Index get_index() const {
        return m_index;
    }

    template <typename T>
    static TypeID get() {
        if constexpr (LAZY_INITIALIZATION) {
            static const Index type_index = s_family_size++;
            return TypeID(type_index);
        } else {
            return TypeID(s_type_index<T>);
        }
    }

    static Index get_family_size() {
        return s_family_size;
    }

private:
    explicit TypeID(Index index)
        : m_index(index) {
    }

    Index m_index;

    inline static Index s_family_size {0};

    template <typename T>
    inline static const Index s_type_index {s_family_size++};

};

} // namespace utl

#endif // UTL_TYPE_ID_HPP
