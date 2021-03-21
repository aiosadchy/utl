#include "test.hpp"

#include <utility>


Test::Test(std::string name)
    : m_name(std::move(name))
    , m_parent(s_current)
    , m_failed(false) {
    s_current = this;
}

Test::~Test() {
    s_current = m_parent;
    (m_failed ? s_tests_failed : s_tests_passed).push_back(get_name(Name::FULL));
}

std::string Test::get_name(Test::Name mode) const {
    if ((mode == Name::SHORT) || (m_parent == nullptr)) {
        return m_name;
    }
    return m_parent->get_name(Name::FULL) + "::" + m_name;
}

void Test::fail() {
    if (m_parent != nullptr) {
        m_parent->fail();
    }
    m_failed = true;
}

Test &Test::get_current() {
    return *s_current;
}

const std::list<std::string> &Test::get_failed_tests() {
    return s_tests_failed;
}

const std::list<std::string> &Test::get_passed_tests() {
    return s_tests_passed;
}

Test *Test::s_current = nullptr;
std::list<std::string> Test::s_tests_failed = {};
std::list<std::string> Test::s_tests_passed = {};
