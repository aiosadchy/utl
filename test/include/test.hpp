#ifndef UTL_TEST_HPP
#define UTL_TEST_HPP

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

class Test {
public:
    enum class Result {
        SUCCESS,
        FAILURE
    };

    using Function = void();

    inline explicit Test(std::string name, Function *function = nullptr);

    inline Result operator()();

    inline const std::string &get_name() const;

    inline void fail();

    inline static const std::vector<std::string> &get_failed_tests();
    inline static const std::vector<std::string> &get_passed_tests();

    inline static Result run_all();

    inline static void print_report();

    inline static Test &get_current_test();

private:
    inline static std::map<std::string, Test &> &get_all_tests();

    inline static std::stack<Test *> &get_tests_being_run_in_current_thread();

    std::string m_name;
    Function   *m_function;
    bool        m_failed;

    inline static std::vector<std::string> s_tests_failed = {};
    inline static std::vector<std::string> s_tests_passed = {};
};

#define ASSERT(...)                                      \
    if (!(__VA_ARGS__)) {                                \
        Test &current_test = Test::get_current_test();   \
        current_test.fail();                             \
        std::cerr << "Test [" << current_test.get_name() \
                  << "], line " << __LINE__              \
                  << ": assertion failed: "              \
                  << #__VA_ARGS__                        \
                  << std::endl;                          \
    }


#define TEST(name)                                       \
    static void execute_test_##name();                   \
    inline Test test_##name{#name, execute_test_##name}; \
    static void execute_test_##name()

#endif // UTL_TEST_HPP

#include "impl/test.inl"
