// (c) Copyright Alexandr Belits 2018

#include <boost/test/unit_test.hpp>
#include "utils/threadsafe_limited_stack.hpp"

BOOST_AUTO_TEST_CASE(test_threadsafe_stack)
{
    using my_treadsafe_limited_stack = utils::threadsafe_limited_stack<int, 5>;
    my_treadsafe_limited_stack stack_;

    BOOST_CHECK_EQUAL(stack_.size(), 0);

    stack_.push(1);

    BOOST_CHECK_EQUAL(stack_.size(), 1);

    stack_.push(2);
    stack_.push(3);
    stack_.push(4);
    stack_.push(5);

    BOOST_CHECK_EQUAL(stack_.size(), 5);
    stack_.push(6);
    BOOST_CHECK_EQUAL(stack_.size(), 5);
    BOOST_CHECK_EQUAL(stack_.wait_and_pop(), 6);
    BOOST_CHECK_EQUAL(stack_.wait_and_pop(), 5);
    BOOST_CHECK_EQUAL(stack_.wait_and_pop(), 4);
    BOOST_CHECK_EQUAL(stack_.wait_and_pop(), 3);
    BOOST_CHECK_EQUAL(stack_.wait_and_pop(), 2);
}
