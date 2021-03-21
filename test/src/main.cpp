#include <iostream>
#include <typeinfo>

#include "tests.hpp"

#include <utl/utl.hpp>

TEST(non_constructible);
TEST(non_copyable);
TEST(range);
TEST(repeat);
TEST(scope_guard);
TEST(static_block);

using namespace utl;

UTL_STATIC_BLOCK {
    std::cout << "static block works" << std::endl;
}

struct S : public TypeInfo<const S, type_traits::Identity, init::TypeInfo::LAZY> {
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

using TestTypeID = TypeID<void, int, type_traits::Decay, init::TypeID::STATIC>;

int main(int, char **) {
    RUN_TEST(non_constructible)
    RUN_TEST(non_copyable)
    RUN_TEST(range)
    RUN_TEST(repeat)
    RUN_TEST(scope_guard)
    RUN_TEST(static_block)
    bool test = false;
    std::cout << "Should be false: " << test << std::endl;
    {
        UTL_SCOPE_GUARD { test = true; };
        std::cout << "Should be false: " << test << std::endl;
    }
    std::cout << "Should be true:  " << test << std::endl;

    std::cout << "Simple TypeID:" << std::endl;
    std::cout << TypeID<void>::get<int>().get_index() << std::endl;
    std::cout << TypeID<void>::get<float>().get_index() << std::endl;
    std::cout << TypeID<void>::get<double>().get_index() << std::endl;
    std::cout << TypeID<void>::get<int>().get_index() << std::endl;
    std::cout << "Family size: " << TypeID<void>::get_types_count() << std::endl;

    std::cout << "TypeID with decay:" << std::endl;
    std::cout << TestTypeID::get<int>().get_index() << std::endl;
    std::cout << TestTypeID::get<const int>().get_index() << std::endl;
    std::cout << TestTypeID::get<double>().get_index() << std::endl;
    std::cout << TestTypeID::get<volatile int &>().get_index() << std::endl;
    std::cout << "Family size: " << TestTypeID::get_types_count() << std::endl;

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

    std::cout << "Tests passed:" << std::endl;
    for (const auto &test : Test::get_passed_tests()) {
        std::cout << "  - " << test << std::endl;
    }

    if (!Test::get_failed_tests().empty()) {
        std::cerr << "There are failed tests:" << std::endl;
        for (const auto &test : Test::get_failed_tests()) {
            std::cerr << "  - " << test << std::endl;
        }
        return 1;
    }

    return 0;
}
