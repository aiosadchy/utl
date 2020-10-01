#include <utl/scope_exit.hpp>
#include <utl/static_block.hpp>
#include <utl/type_id.hpp>
#include <iostream>

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
    return 0;
}