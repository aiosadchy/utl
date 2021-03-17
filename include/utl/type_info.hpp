#ifndef UTL_TYPE_INFO_HPP
#define UTL_TYPE_INFO_HPP

#include "utl/type_traits.hpp"

namespace utl {

namespace init {

    enum class TypeInfo {
        LAZY,
        STATIC
    };

} // namespace init


template <
        typename TData,
        template <typename> typename TDecay = utl::type_traits::Identity,
        init::TypeInfo V_INIT_MODE = init::TypeInfo::LAZY
>
class TypeInfo {
public:
    using Data = TData;

    template <typename T>
    class Initializer {};

    template <typename T>
    static Data &get() {
        if constexpr (type_traits::is_same<T, TDecay<T>>) {
            if constexpr (V_INIT_MODE == init::TypeInfo::LAZY) {
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
