#include <boost/test/unit_test.hpp>
#include <cmath>
#include "degree_module.hpp"

BOOST_AUTO_TEST_SUITE(ModuleDegree)
BOOST_AUTO_TEST_SUITE(Construct)
using namespace earth_math;
using degree360 = degree_module<360>;
degree_abstract res1(30, 0, 0, 0);
degree_abstract res2(330, 0, 0, 0);
BOOST_AUTO_TEST_CASE(test_create_from_degree)
{
    const auto deg = degree360::from_degree(30.);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res1.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_create_from_sec)
{
    const auto deg = degree360::from_seconds(30 * 60 * 60);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res1.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_create_from_neg_degree)
{
    const auto deg = degree360::from_degree(-30.);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res2.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_create_from_neg_sec)
{
    const auto deg = degree360::from_seconds(-30 * 60 * 60);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res2.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_create_from_big_degree)
{
    const auto deg = degree360::from_degree(360. * 10e7 + 30);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res1.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_create_from_big_sec)
{
    const auto s = 360ll * 60ll * 60ll * 1000000000ll + 30ll * 60ll * 60ll;
    const auto deg = degree360::from_seconds(s);
    BOOST_CHECK_EQUAL(deg.to_string(show_seconds),
                      res1.to_string(show_seconds));
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
