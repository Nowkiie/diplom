
// (c) Copyright Dmitriy Shikhov 2023

#include <chrono>
#include <thread>
#include <boost/test/unit_test.hpp>
#include <utils/multi_active.hpp>

using namespace std::this_thread;
using namespace std::chrono;

BOOST_AUTO_TEST_SUITE(multi_active)

BOOST_AUTO_TEST_CASE(size)
{
    const size_t actives_count = 4;
    utils::multi_active multi_active(actives_count);

    BOOST_CHECK_EQUAL(multi_active.size(), 0);

    bool wait = true;
    const auto wait_task = [&wait]
    {
        while (wait)
            ;
    };
    // Одна задача на выполнение, вторая в очередь. Просто всем поставить
    // задачу на выполнение невозможно из-за алгоритма распределения задач
    for (size_t i = 0; i < actives_count * 2; ++i)
    {
        multi_active.push_task(wait_task);
    }

    sleep_for(milliseconds(100));

    BOOST_CHECK_EQUAL(multi_active.size(), actives_count);

    multi_active.clear();

    const auto nop_task = []
    {
    };
    multi_active.push_task(nop_task);
    multi_active.push_task(nop_task);
    multi_active.push_task(nop_task);

    sleep_for(milliseconds(100));
    BOOST_CHECK_EQUAL(multi_active.size(), 3);

    wait = false;

    sleep_for(milliseconds(100));
    BOOST_CHECK_EQUAL(multi_active.size(), 0);
}

BOOST_AUTO_TEST_CASE(stop_empty)
{
    utils::multi_active multi_active(4);

    multi_active.stop();

    BOOST_TEST(multi_active.size() == 0);
}

BOOST_AUTO_TEST_CASE(stop_nonempty)
{
    utils::multi_active multi_active(4);

    multi_active.push_task(
        []
        {
        });

    multi_active.stop();

    BOOST_TEST(multi_active.size() == 0);
}

BOOST_AUTO_TEST_CASE(push_task_after_stop)
{
    utils::multi_active multi_active(4);

    const auto task = []
    {
    };

    multi_active.push_task(task);
    multi_active.stop();

    BOOST_TEST(multi_active.size() == 0);

    multi_active.push_task(task);

    BOOST_TEST(multi_active.size() == 0);
}

BOOST_AUTO_TEST_CASE(name)
{
    const std::string name = "TestActive";
    utils::multi_active multi_active(1, name);

    std::string actual_name;
    multi_active.push_task(
        [&actual_name]
        {
            actual_name = utils::thread_name();
        });

    multi_active.stop();

    BOOST_TEST(name + "-0" == actual_name);
}

BOOST_AUTO_TEST_SUITE_END()
