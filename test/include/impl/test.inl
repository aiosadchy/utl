#ifndef UTL_TEST_INL
#define UTL_TEST_INL

#ifndef UTL_TEST_HPP
#include "test.hpp"
#endif

#include <stdexcept>

Test::Test(std::string name, Function *function)
    : m_name(std::move(name))
    , m_function(function)
    , m_failed(false) {
    get_all_tests().emplace(m_name, *this);
}

Test::Result Test::operator()() {
    m_failed = false;
    get_tests_being_run_in_current_thread().emplace(this);
    try {
        m_function();
    } catch (const std::exception &exception) {
        fail();
        std::cerr << "Test [" << get_name()
                  << "]: an exception occurred: "
                  << exception.what()
                  << std::endl;
    }
    get_tests_being_run_in_current_thread().pop();
    (m_failed ? s_tests_failed : s_tests_passed).emplace_back(get_name());
    return m_failed ? Result::FAILURE : Result::SUCCESS;
}

const std::string &Test::get_name() const {
    return m_name;
}

void Test::fail() {
    m_failed = true;
}

const std::vector<std::string> &Test::get_failed_tests() {
    return s_tests_failed;
}

const std::vector<std::string> &Test::get_passed_tests() {
    return s_tests_passed;
}

Test::Result Test::run_all() {
    Result result = Result::SUCCESS;
    for (auto &[name, test] : get_all_tests()) {
        result = (test() == Result::SUCCESS) ? result : Result::FAILURE;
    }
    return result;
}

void Test::print_report() {
    if (!get_passed_tests().empty()) {
        std::cout << "Tests passed:" << std::endl;
        for (const auto &test : get_passed_tests()) {
            std::cout << "  - " << test << std::endl;
        }
    }

    if (!get_failed_tests().empty()) {
        std::cout << "Tests failed:" << std::endl;
        for (const auto &test : get_failed_tests()) {
            std::cout << "  - " << test << std::endl;
        }
    }
}

Test &Test::get_current_test() {
    auto &tests_being_run = get_tests_being_run_in_current_thread();
    if (tests_being_run.empty()) {
        throw std::logic_error{"there are no tests being run in the current thread"};
    }
    return *get_tests_being_run_in_current_thread().top();
}

std::map<std::string, Test &> &Test::get_all_tests() {
    static std::map<std::string, Test &> all_tests = {};
    return all_tests;
}

std::stack<Test *> &Test::get_tests_being_run_in_current_thread() {
    thread_local std::stack<Test *> tests_being_run = {};
    return tests_being_run;
}

#endif // UTL_TEST_INL
