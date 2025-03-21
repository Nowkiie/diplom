
// (c) Copyright Dmitriy Shikhov 2020

#include <boost/test/unit_test.hpp>
#include "utils/event.hpp"
#include <optional>
#include <thread>

BOOST_AUTO_TEST_SUITE(event)

BOOST_AUTO_TEST_CASE(test_reset)
{
    utils::event e;

    e.notify();
    BOOST_TEST(e.get() == 1);

    e.notify();
    BOOST_TEST(e.get() == 2);

    e.notify();
    BOOST_TEST(e.get() == 3);

    e.reset();
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_in_single_thread)
{
    utils::event e;

    e.notify();
    BOOST_TEST(e.get() == 1);

    e.wait();
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_in_multi_thread)
{
    utils::event e;
    std::atomic_bool before_wait{false};
    std::atomic_bool after_wait{false};
    std::thread thread{
        [&e, &before_wait, &after_wait]
        {
            before_wait = true;
            e.wait();
            after_wait = true;
        }};

    while (!before_wait)
    {
        std::this_thread::yield();
    }
    std::this_thread::sleep_for(std::chrono::seconds{1});

    BOOST_TEST((before_wait && !after_wait));
    BOOST_TEST(e.get() == 0);

    e.notify();
    thread.join();

    BOOST_TEST((before_wait && after_wait));
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_for_with_unreached_timeout)
{
    utils::event e;
    std::atomic_bool before_wait{false};
    std::atomic_bool after_wait{false};
    std::optional<bool> result;
    std::thread thread{
        [&e, &before_wait, &after_wait, &result]
        {
            before_wait = true;
            result = e.wait_for(std::chrono::hours{1});
            after_wait = true;
        }};

    while (!before_wait)
    {
        std::this_thread::yield();
    }
    std::this_thread::sleep_for(std::chrono::seconds{1});

    BOOST_TEST((before_wait && !after_wait));
    BOOST_TEST(e.get() == 0);

    e.notify();
    thread.join();

    BOOST_TEST(*result);
    BOOST_TEST((before_wait && after_wait));
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_for_with_timeout)
{
    utils::event e;
    std::atomic_bool before_wait{false};
    std::atomic_bool after_wait{false};
    std::optional<bool> result;
    std::thread thread{
        [&e, &before_wait, &after_wait, &result]
        {
            before_wait = true;
            result = e.wait_for(std::chrono::seconds{1});
            after_wait = true;
        }};

    while (!before_wait)
    {
        std::this_thread::yield();
    }

    BOOST_TEST((before_wait && !after_wait));
    BOOST_TEST(e.get() == 0);

    thread.join();

    BOOST_TEST(!*result);
    BOOST_TEST((before_wait && after_wait));
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_until_with_unreached_timeout)
{
    utils::event e;
    std::atomic_bool before_wait{false};
    std::atomic_bool after_wait{false};
    std::optional<bool> result;
    std::thread thread{
        [&e, &before_wait, &after_wait, &result]
        {
            before_wait = true;
            result = e.wait_until(std::chrono::high_resolution_clock::now()
                                  + std::chrono::hours{1});
            after_wait = true;
        }};

    while (!before_wait)
    {
        std::this_thread::yield();
    }
    std::this_thread::sleep_for(std::chrono::seconds{1});

    BOOST_TEST((before_wait && !after_wait));
    BOOST_TEST(e.get() == 0);

    e.notify();
    thread.join();

    BOOST_TEST(*result);
    BOOST_TEST((before_wait && after_wait));
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_CASE(test_wait_until_with_timeout)
{
    utils::event e;
    std::atomic_bool before_wait{false};
    std::atomic_bool after_wait{false};
    std::optional<bool> result;
    std::thread thread{
        [&e, &before_wait, &after_wait, &result]
        {
            before_wait = true;
            result = e.wait_until(std::chrono::high_resolution_clock::now()
                                  + std::chrono::seconds{1});
            after_wait = true;
        }};

    while (!before_wait)
    {
        std::this_thread::yield();
    }

    BOOST_TEST((before_wait && !after_wait));
    BOOST_TEST(e.get() == 0);

    thread.join();

    BOOST_TEST(!*result);
    BOOST_TEST((before_wait && after_wait));
    BOOST_TEST(e.get() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
