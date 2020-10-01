#include <utl/scope_exit.hpp>
#include <utl/static_block.hpp>
#include <utl/type_id.hpp>
#include <iostream>
#include <utl/storage.hpp>

STATIC_BLOCK {
    std::cout << "static block works" << std::endl;
}


int main(int, char **) {
    std::cout << "Family size: " << TypeID<void>::get_family_size() << std::endl;
    bool test = false;
    std::cout << test << std::endl;
    {
        SCOPE_EXIT { test = true; };
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
    return 0;
}