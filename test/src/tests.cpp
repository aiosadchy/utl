#include "tests.hpp"

Test::Test(std::string name)
    : m_name(std::move(name))
    , m_failed_at_start(s_tests_failed.size())
    , m_failed(false) {
}

Test::~Test() {
    if (m_failed_at_start != s_tests_failed.size()) {
        m_failed = true;
    }
    (m_failed ? s_tests_failed : s_tests_passed).push_back(m_name);
}

const std::string &Test::get_name() const {
    return m_name;
}

void Test::set_failed(bool failed) {
    m_failed = failed;
}

const std::list<std::string> &Test::get_failed_tests() {
    return s_tests_failed;
}

const std::list<std::string> &Test::get_passed_tests() {
    return s_tests_passed;
}

std::list<std::string> Test::s_tests_failed = {};
std::list<std::string> Test::s_tests_passed = {};
