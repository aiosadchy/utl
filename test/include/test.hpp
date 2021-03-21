#ifndef UTL_TEST_HPP
#define UTL_TEST_HPP

#include <iostream>
#include <list>
#include <string>


class Test {
public:
    enum class Name {
        SHORT,
        FULL
    };

    explicit Test(std::string name);
    ~Test();

    std::string get_name(Name mode = Name::SHORT) const;
    void fail();

    static Test &get_current();

    static const std::list<std::string> &get_failed_tests();
    static const std::list<std::string> &get_passed_tests();

private:
    std::string m_name;
    Test *m_parent;
    bool m_failed;

    static Test *s_current;
    static std::list<std::string> s_tests_failed;
    static std::list<std::string> s_tests_passed;

};

#define TEST(name) \
    void test_##name(Test = Test(#name))

#define RUN_TEST(name) \
    test_##name();

#define ASSERT(...)                                             \
    if (!(__VA_ARGS__)) {                                       \
        Test::get_current().fail();                             \
        std::cerr << "Test " << Test::get_current().get_name()  \
                  << ", line " << __LINE__                      \
                  << ": assertion failed: "                     \
                  << #__VA_ARGS__                               \
                  << std::endl;                                 \
    }


#endif // UTL_TEST_HPP
