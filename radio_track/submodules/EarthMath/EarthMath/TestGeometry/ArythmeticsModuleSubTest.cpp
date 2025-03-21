#include <boost/test/unit_test.hpp>
#include "degree_module.hpp"

BOOST_AUTO_TEST_SUITE(ModuleDegree)
BOOST_AUTO_TEST_SUITE(ArithmeticSub)
using namespace earth_math;
using degree360 = degree_module<360>;

BOOST_AUTO_TEST_CASE(test_simple_sub)
{
    const auto a = degree360::from_degree(30.);
    const auto b = degree360::from_degree(180.);
    const auto c = b - a;
    BOOST_CHECK_EQUAL(c.to_string(show_seconds), "150\xC2\xB0 00' 00''");
}
BOOST_AUTO_TEST_CASE(test_overload_sub)
{
    const auto a = degree360::from_degree(30.);
    const auto b = degree360::from_degree(340.);
    const auto c = a - b;
    BOOST_CHECK_EQUAL(c.to_string(show_seconds), "50\xC2\xB0 00' 00''");
}
BOOST_AUTO_TEST_CASE(test_many_overload_sub)
{
    const auto a = degree360::from_degree(30.);
    const auto b = degree360::from_degree(340.);
    const auto c = a - b - b - b;
    BOOST_CHECK_EQUAL(c.to_string(show_seconds), "90\xC2\xB0 00' 00''");
}
BOOST_AUTO_TEST_CASE(test_zero_sub)
{
    const auto a = degree360::from_degree(330.);
    const auto b = degree360::from_degree(330.);
    const auto c = a - b;
    BOOST_CHECK_EQUAL(c.to_string(show_seconds), "0\xC2\xB0 00' 00''");
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
