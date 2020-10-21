#include <iostream>
#include <typeinfo>

#include <utl/scope_exit.hpp>
#include <utl/static_block.hpp>
#include <utl/type_id.hpp>
#include <utl/type_info.hpp>
#include <utl/storage.hpp>
#include <utl/range.hpp>
#include <utl/repeat.hpp>

using namespace utl;

UTL_STATIC_BLOCK {
    std::cout << "static block works" << std::endl;
}

struct S : public TypeInfo<const S> {
    template <typename T>
    explicit S(TypeInfo::Initializer<T>)
        : size(sizeof(T))
        , align(alignof(T))
        , name(typeid(T).name())
        , next(s_begin) {
        s_begin = this;
    }

    int size;
    int align;
    std::string name;
    S *next;

    inline static S *s_begin = nullptr;

};

int main(int, char **) {
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
    std::cout << "Family size: " << TypeID<void>::get_registered_types_count() << std::endl;

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

    for (S *it = S::s_begin; it != nullptr; it = it->next) {
        std::cout << it->name << ": " << it->size << ", " << it->align << std::endl;
    }

    UTL_REPEAT(1 + 2) {
        std::cout << "Looping..." << std::endl;
    }

    return 0;
}