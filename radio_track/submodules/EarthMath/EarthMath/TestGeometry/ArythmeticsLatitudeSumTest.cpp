#include <boost/test/unit_test.hpp>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Latitude)
BOOST_AUTO_TEST_SUITE(ArythmeticsLatitudeSum)
using namespace earth_math;
degree_latitude x1(75, 55, 55, 333, true);
degree_latitude x2(22, 22, 22, 888, true);
degree_latitude x3(22, 22, 22, 888);
degree_latitude x4(75, 55, 55, 333);
degree_longitude x5(75, 55, 55, 333);
degree_abstract y1(22, 22, 22, 888, true);
std::string res1 = "81\xC2\xB0 41' 41'' 779'''";
std::string res2 = "53\xC2\xB0 33' 32'' 445'''";
std::string zero = "0\xC2\xB0 00' 00'' 000'''";
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_01)
{
    BOOST_CHECK_EQUAL((x1 + x2).to_string(show_milliseconds), res1 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_01_1)
{
    BOOST_CHECK_EQUAL((x1 + y1).to_string(show_milliseconds),
                      (x1 + x2).to_string(show_milliseconds));
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_01_2)
{
    BOOST_CHECK_NE((y1 + x1).to_string(show_milliseconds),
                   (x1 + x2).to_string(show_milliseconds));
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_02)
{
    BOOST_CHECK_EQUAL((x1 + x3).to_string(show_milliseconds), res2 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_03)
{
    BOOST_CHECK_EQUAL((x1 + x4).to_string(show_milliseconds), zero);
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_04)
{
    BOOST_CHECK_EQUAL((x2 + x4).to_string(show_milliseconds), res2 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_05)
{
    BOOST_CHECK_EQUAL((x3 + x4).to_string(show_milliseconds), res1 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_06)
{
    BOOST_CHECK_EQUAL((x3 + x2).to_string(show_milliseconds), zero);
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_07)
{
    BOOST_CHECK_EQUAL((x3 + x1).to_string(show_milliseconds), res2 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_08)
{
    BOOST_CHECK_EQUAL((x4 + x2).to_string(show_milliseconds), res2 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_invallid_usage)
{
    // BOOST_CHECK_EQUAL((x5 + x2).ToString(show_milliseconds), res2 + " с.ш.");
    BOOST_CHECK_EQUAL(true, true);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
