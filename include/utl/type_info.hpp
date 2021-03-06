#ifndef UTL_TYPE_INFO_HPP
#define UTL_TYPE_INFO_HPP

#include "utl/type_traits.hpp"

namespace utl {

template <
        typename TData,
        template <typename> typename TDecay = utl::type_traits::Identity,
        bool LAZY_INITIALIZATION = true
>
class TypeInfo {
public:
    using Data = TData;

    template <typename T>
    class Initializer {};

    template <typename T>
    static Data &get() {
        if constexpr (type_traits::is_same<T, TDecay<T>>) {
            if constexpr (LAZY_INITIALIZATION) {
                static Data type_data{Initializer<T>()};
                return type_data;
            } else {
                return s_type_data<T>;
            }
        } else {
            return get<TDecay<T>>();
        }
    }

private:
    template <typename T>
    inline static Data s_type_data{Initializer<T>()};

};

} // namespace utl

#endif // UTL_TYPE_INFO_HPP
