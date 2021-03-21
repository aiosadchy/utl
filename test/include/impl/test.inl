#ifndef UTL_TEST_INL
#define UTL_TEST_INL

#include "test.hpp"


Test::Test(std::string name, Function *function)
    : m_name(std::move(name))
    , m_function(function)
    , m_failed(false) {
    get_all_tests().emplace(m_name, *this);
}

Test::Result Test::operator()() {
    m_failed = false;
    m_function(*this);
    (m_failed ? s_tests_failed : s_tests_passed).push_back(get_name());
    return m_failed ? Result::FAILURE : Result::SUCCESS;
}

std::string Test::get_name() const {
    return m_name;
}

void Test::fail() {
    m_failed = true;
}

const std::list<std::string> &Test::get_failed_tests() {
    return s_tests_failed;
}

const std::list<std::string> &Test::get_passed_tests() {
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
        std::cerr << "There are failed tests:" << std::endl;
        for (const auto &test : get_failed_tests()) {
            std::cerr << "  - " << test << std::endl;
        }
    }
}

std::map<std::string, Test &> &Test::get_all_tests() {
    static std::map<std::string, Test &> all_tests = {};
    return all_tests;
}

#endif // UTL_TEST_INL
