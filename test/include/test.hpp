#ifndef UTL_TEST_HPP
#define UTL_TEST_HPP

#include <iostream>
#include <list>
#include <map>
#include <string>


class Test {
public:
    enum class Result {
        SUCCESS,
        FAILURE
    };

    using Function = void (Test &);

    inline explicit Test(std::string name, Function *function = nullptr);

    inline Result operator()();

    inline std::string get_name() const;
    inline void fail();

    inline static const std::list<std::string> &get_failed_tests();
    inline static const std::list<std::string> &get_passed_tests();

    inline static Result run_all();
    inline static void print_report();

private:
    inline static std::map<std::string, Test &> &get_all_tests();

    std::string m_name;
    Function *m_function;
    bool m_failed;

    inline static std::list<std::string> s_tests_failed = {};
    inline static std::list<std::string> s_tests_passed = {};

};


#define CURRENT_TEST test_current_state


#define ASSERT(...)                                         \
    if (!(__VA_ARGS__)) {                                   \
        CURRENT_TEST.fail();                                \
        std::cerr << "Test [" << CURRENT_TEST.get_name()    \
                  << "], line " << __LINE__                 \
                  << ": assertion failed: "                 \
                  << #__VA_ARGS__                           \
                  << std::endl;                             \
    }


#define TEST(name)                                                  \
    void execute_test_##name(Test &CURRENT_TEST);                   \
    inline Test test_##name{#name, execute_test_##name};            \
    void execute_test_##name([[maybe_unused]] Test &CURRENT_TEST)


#define TEST_MAIN                                           \
    int main(int, char **) {                                \
        Test::Result result = Test::run_all();              \
        Test::print_report();                               \
        return (result == Test::Result::FAILURE) ? 1 : 0;   \
    }

#endif // UTL_TEST_HPP

#include "impl/test.inl"
