#include <utl/scope_exit.hpp>
#include <utl/static_block.hpp>
#include <iostream>

STATIC_BLOCK {
    std::cout << "static block works" << std::endl;
};

int main(int, char **) {
    bool test = false;
    std::cout << test << std::endl;
    {
        SCOPE_EXIT { test = true; };
    }
    std::cout << test << std::endl;
    return 0;
}