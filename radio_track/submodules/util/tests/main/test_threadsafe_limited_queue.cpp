// (c) Copyright Alexandr Belits 2018

#include <boost/test/unit_test.hpp>
#include "utils/threadsafe_limited_queue.hpp"

BOOST_AUTO_TEST_CASE(test_threadsafe_limited_queue)
{
    using my_treadsafe_limited_stack = utils::threadsafe_limited_queue<int, 5>;
    my_treadsafe_limited_stack limited_queue_;

    BOOST_CHECK_EQUAL(limited_queue_.size(), 0);

    limited_queue_.push(1);

    BOOST_CHECK_EQUAL(limited_queue_.size(), 1);

    limited_queue_.push(2);
    limited_queue_.push(3);
    limited_queue_.push(4);
    limited_queue_.push(5);

    BOOST_CHECK_EQUAL(limited_queue_.size(), 5);
    limited_queue_.push(6);
    BOOST_CHECK_EQUAL(limited_queue_.size(), 5);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 2);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 3);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 4);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 5);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 6);
}
