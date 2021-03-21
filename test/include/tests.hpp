#ifndef UTL_TESTS_HPP
#define UTL_TESTS_HPP

#include <iostream>
#include <list>
#include <string>
#include <utility>


// TODO: track parent test
class Test {
public:
    explicit Test(std::string name);
    ~Test();

    [[nodiscard]] const std::string &get_name() const;
    void set_failed(bool failed);

    static const std::list<std::string> &get_failed_tests();
    static const std::list<std::string> &get_passed_tests();

private:
    std::string m_name;
    std::size_t m_failed_at_start;
    bool m_failed;

    static std::list<std::string> s_tests_failed;
    static std::list<std::string> s_tests_passed;

};

#define TEST(name) \
    void test_##name([[maybe_unused]] Test &&current_test = Test(#name))

#define RUN_TEST(name) \
    test_##name();

#define ASSERT(...)                             \
    if (!(__VA_ARGS__)) {                       \
        std::cerr << current_test.get_name()    \
                  << ", line " << __LINE__      \
                  << ": assertion failed: "     \
                  << #__VA_ARGS__               \
                  << std::endl;                 \
        current_test.set_failed(true);          \
    }


#endif // UTL_TESTS_HPP
