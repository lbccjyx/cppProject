// test/test_calculator.cpp
#pragma once
#include <iostream>
#include <boost/test/unit_test.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_AUTO_TEST_SUITE(calculator_tests)

BOOST_AUTO_TEST_CASE(addition_test) {
    BOOST_CHECK_EQUAL(add(2, 3), 5);
    BOOST_CHECK_EQUAL(add(-1, 1), 0);
    BOOST_CHECK_EQUAL(add(0, 0), 0);
    std::cout<<"hello world\n";
}

BOOST_AUTO_TEST_SUITE_END()

