
// (c) Copyright Dmitriy Shikhov 2016

#include <boost/test/unit_test.hpp>
#include "utils/threadsafe_queue.hpp"

BOOST_AUTO_TEST_CASE(test_threadsafe_queue_size_method)
{
    utils::threadsafe_queue<int> queue;

    BOOST_CHECK_EQUAL(queue.size(), 0);

    queue.push(1);

    BOOST_CHECK_EQUAL(queue.size(), 1);

    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    BOOST_CHECK_EQUAL(queue.size(), 5);
}
