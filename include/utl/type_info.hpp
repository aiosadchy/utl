#ifndef UTL_TYPE_INFO_HPP
#define UTL_TYPE_INFO_HPP

#include "utl/common.hpp"
#include "utl/type.hpp"

namespace UTL_NAMESPACE {

template <typename TData>
class TypeInfo {
public:
    using Data = TData;

    template <typename T>
    static const Data &get() {
        return s_type_data<T>;
    }

private:
    template <typename T>
    inline static const Data s_type_data {Type<T>()};

};

} // namespace UTL_NAMESPACE

#endif // UTL_TYPE_INFO_HPP
