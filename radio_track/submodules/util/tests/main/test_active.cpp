
// (c) Copyright Dmitriy Shikhov 2016, 2018, 2023

#include <chrono>
#include <thread>
#include <boost/test/unit_test.hpp>
#include <utils/active.hpp>
#include <utils/threadsafe_limited_queue.hpp>
#include <utils/threadsafe_limited_stack.hpp>
#include <utils/threadsafe_list.hpp>

using namespace std::this_thread;
using namespace std::chrono;

BOOST_AUTO_TEST_SUITE(active)

BOOST_AUTO_TEST_CASE(size)
{
    utils::active active;

    BOOST_CHECK_EQUAL(active.size(), 0);

    bool wait = true;
    active.push_task(
        [&wait]
        {
            while (wait)
                ;
        });

    sleep_for(milliseconds(100));

    // one task will be in work loop

    BOOST_CHECK_EQUAL(active.size(), 0);

    active.push_task(
        []
        {
        });
    active.push_task(
        []
        {
        });
    active.push_task(
        []
        {
        });

    sleep_for(milliseconds(100));
    BOOST_CHECK_EQUAL(active.size(), 3);

    wait = false;

    sleep_for(milliseconds(100));
    BOOST_CHECK_EQUAL(active.size(), 0);
}

BOOST_AUTO_TEST_CASE(stop_empty)
{
    utils::active active;

    active.stop();

    BOOST_TEST(active.size() == 0);
}

BOOST_AUTO_TEST_CASE(stop_nonempty)
{
    utils::active active;

    active.push_task(
        []
        {
        });

    active.stop();

    BOOST_TEST(active.size() == 0);
}

BOOST_AUTO_TEST_CASE(push_task_after_stop)
{
    utils::active active;

    const auto task = []
    {
    };

    active.push_task(task);
    active.stop();

    BOOST_TEST(active.size() == 0);

    active.push_task(task);

    BOOST_TEST(active.size() == 0);
}

BOOST_AUTO_TEST_CASE(name)
{
    const std::string name = "TestActive";
    utils::active active(name);

    std::string actual_name;
    active.push_task(
        [&actual_name]
        {
            actual_name = utils::thread_name();
        });

    active.stop();

    BOOST_TEST(name == actual_name);
}

BOOST_AUTO_TEST_CASE(alternative_containers_size)
{
    using namespace utils;

    (void)active_template<default_treadsafe_limited_queue>{}.size();
    (void)active_template<default_treadsafe_limited_stack>{}.size();
    (void)active_template<threadsafe_list>{}.size();
}

BOOST_AUTO_TEST_SUITE_END()
