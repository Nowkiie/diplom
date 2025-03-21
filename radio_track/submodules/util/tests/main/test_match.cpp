
// (c) Copyright Dmitriy Shikhov 2018

#include <memory>
#include <boost/test/unit_test.hpp>
#include "utils/match.hpp"

BOOST_AUTO_TEST_SUITE(match)

BOOST_AUTO_TEST_CASE(all_cases_explicit)
{
    const auto etalon = std::string{"abc"};
    std::variant<int, float, double, std::string> variant = etalon;

    bool is_matched = false;
    utils::match(
        variant,
        [](int)
        {
            BOOST_TEST_ERROR("Wrong int case.");
        },
        [](float)
        {
            BOOST_TEST_ERROR("Wrong float case.");
        },
        [](double)
        {
            BOOST_TEST_ERROR("Wrong double case.");
        },
        [&etalon, &is_matched](std::string const& value)
        {
            BOOST_TEST(value == etalon);
            is_matched = true;
        });

    BOOST_TEST(is_matched);
}

BOOST_AUTO_TEST_CASE(default_auto_case)
{
    const auto etalon = std::string{"abc"};
    std::variant<int, float, double, std::string> variant = etalon;

    bool is_matched = false;
    utils::match(
        variant,
        [](auto)
        {
            BOOST_TEST_ERROR("Wrong default case.");
        },
        [&etalon, &is_matched](std::string const& value)
        {
            BOOST_TEST(value == etalon);
            is_matched = true;
        });

    BOOST_TEST(is_matched);
}

BOOST_AUTO_TEST_SUITE_END()
