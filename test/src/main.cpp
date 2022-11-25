#include <cstdlib>

#include "test.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[]) {
    Test::Result result = Test::run_all();
    Test::print_report();
    return (result == Test::Result::FAILURE) ? EXIT_FAILURE : EXIT_SUCCESS;
}
