#ifndef UTL_TYPE_INFO_HPP
#define UTL_TYPE_INFO_HPP

namespace utl {

template <typename TData>
class TypeInfo {
public:
    using Data = TData;

    template <typename T>
    class Initializer {
    };

    template <typename T>
    static Data &get() {
        return s_type_data<T>;
    }

private:
    template <typename T>
    inline static Data s_type_data {Initializer<T>()};

};

} // namespace utl

#endif // UTL_TYPE_INFO_HPP
