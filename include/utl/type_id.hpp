#ifndef UTL_TYPE_ID_HPP
#define UTL_TYPE_ID_HPP

template <typename Family, typename Index = unsigned short int>
class TypeID {
public:
    TypeID()
        : m_index(Index(0) - Index(1)) {
    }

    Index get_index() const {
        return m_index;
    }

    template <typename T>
    static TypeID get() {
        return TypeID(s_type_index<T>);
    }

    static Index get_family_size() {
        return s_family_size;
    }

private:
    explicit TypeID(Index index)
        : m_index(index) {
    }

    Index m_index;

    inline static Index s_family_size = Index(0);

    template <typename T>
    inline static const Index s_type_index = s_family_size++;

};

#endif // UTL_TYPE_ID_HPP
