#include <utl/scope_exit.hpp>
#include <iostream>

int main(int, char **) {
    bool test = false;
    std::cout << test << std::endl;
    {
        SCOPE_EXIT { test = true; };
    }
    std::cout << test << std::endl;
    return 0;
}