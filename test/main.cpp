#include <iostream>
#include <typeinfo>

#include <utl/scope_exit.hpp>
#include <utl/static_block.hpp>
#include <utl/type_id.hpp>
#include <utl/type_info.hpp>
#include <utl/storage.hpp>
#include <utl/range.hpp>

using namespace utl;

UTL_STATIC_BLOCK {
    std::cout << "static block works" << std::endl;
}

struct S : public TypeInfo<S> {
    template <typename T>
    explicit S(Type<T>)
        : size(sizeof(T))
        , align(alignof(T))
        , name(typeid(T).name()) {
    }

    int size;
    int align;
    std::string name;

};

int main(int, char **) {
    std::cout << "Family size: " << TypeID<void>::get_family_size() << std::endl;
    bool test = false;
    std::cout << test << std::endl;
    {
        UTL_SCOPE_EXIT { test = true; };
    }
    std::cout << test << std::endl;
    std::cout << TypeID<void>::get<int>().get_index() << std::endl;
    std::cout << TypeID<void>::get<float>().get_index() << std::endl;
    std::cout << TypeID<void>::get<double>().get_index() << std::endl;
    std::cout << TypeID<void>::get<int>().get_index() << std::endl;

    Storage<int> int_storage;
    new (int_storage.ptr()) int(15);
    std::cout << int_storage.ref() << std::endl;
    static_assert(std::is_standard_layout_v<Storage<int>>);

    for (int i : Range(10)) {
        std::cout << i << ", ";
    }
    std::cout << "that's all" << std::endl;

    S s = S::get<int>();
    std::cout << s.name << ": " << s.size << ", " << s.align << std::endl;
    s = S::get<char>();
    std::cout << s.name << ": " << s.size << ", " << s.align << std::endl;
    s = S::get<S>();
    std::cout << s.name << ": " << s.size << ", " << s.align << std::endl;

    return 0;
}