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
    using Decay = TDecay<T>;

    static constexpr init::TypeInfo INIT_MODE = V_INIT_MODE;

    template <typename T>
    class Initializer {};

    template <typename T>
    static Data &get() {
        return get_without_decay<Decay<T>>();
    }

private:
    template <typename T>
    static Data &get_without_decay() {
        if constexpr (INIT_MODE == init::TypeInfo::LAZY) {
            static Data type_data{Initializer<T>()};
            return type_data;
        } else {
            return s_type_data<T>;
        }
    }

    template <typename T>
    inline static Data s_type_data{Initializer<T>()};

};

} // namespace utl

#endif // UTL_TYPE_INFO_HPP
