// (c) Copyright Konstantin Krasheninnikov 2018

#include <boost/test/unit_test.hpp>
#include "utils/threadsafe_list.hpp"

BOOST_AUTO_TEST_CASE(test_threadsafe_list_queue)
{
    using namespace utils;
    threadsafe_list<int> limited_queue_;

    BOOST_CHECK_EQUAL(limited_queue_.size(), 0);

    limited_queue_.push(1, insert_place::begin);

    BOOST_CHECK_EQUAL(limited_queue_.size(), 1);

    limited_queue_.push(2, insert_place::end);
    limited_queue_.push(3, insert_place::begin);
    limited_queue_.push(4, insert_place::end);
    limited_queue_.push(5, insert_place::begin);
    limited_queue_.push(6, insert_place::end);

    BOOST_CHECK_EQUAL(limited_queue_.size(), 6);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 5);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 3);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 1);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 2);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 4);
    BOOST_CHECK_EQUAL(limited_queue_.wait_and_pop(), 6);
}
