
// (c) Copyright Dmitriy Shikhov 2023

#include <boost/test/unit_test.hpp>
#include "utils/string_utils.hpp"

BOOST_AUTO_TEST_SUITE(string_utils)

BOOST_AUTO_TEST_CASE(ltrim)
{
    std::string s{"  a  b  c  "};
    utils::ltrim(s);

    BOOST_TEST(s == "a  b  c  ");
}

BOOST_AUTO_TEST_CASE(rtrim)
{
    std::string s{"  a  b  c  "};
    utils::rtrim(s);

    BOOST_TEST(s == "  a  b  c");
}

BOOST_AUTO_TEST_CASE(trim)
{
    std::string s{"  a  b  c  "};
    utils::trim(s);

    BOOST_TEST(s == "a  b  c");
}

BOOST_AUTO_TEST_SUITE_END()
