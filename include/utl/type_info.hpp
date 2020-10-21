#ifndef UTL_TYPE_INFO_HPP
#define UTL_TYPE_INFO_HPP

namespace utl {

template <typename TData, bool LAZY_INITIALIZATION = false>
class TypeInfo {
public:
    using Data = TData;

    template <typename T>
    class Initializer {
    public:
        using Type = T;

    };

    template <typename T>
    static Data &get() {
        if constexpr (LAZY_INITIALIZATION) {
            static Data type_data {Initializer<T>()};
            return type_data;
        } else {
            return s_type_data<T>;
        }
    }

private:
    template <typename T>
    inline static Data s_type_data {Initializer<T>()};

};

} // namespace utl

#endif // UTL_TYPE_INFO_HPP
