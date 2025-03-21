#include <boost/test/unit_test.hpp>
#include "Degree.hpp"
BOOST_AUTO_TEST_SUITE(Longitude)
BOOST_AUTO_TEST_SUITE(ArythmeticsLongitudeSub)
using namespace earth_math;
degree_longitude x1(175, 55, 55, 333, true);
degree_longitude x2(22, 22, 22, 888, true);
degree_longitude x3(22, 22, 22, 888);
degree_longitude x4(175, 55, 55, 333);

std::string res1 = "161\xC2\xB0 41' 41'' 779'''";
std::string res2 = "153\xC2\xB0 33' 32'' 445'''";
std::string res3 = "8\xC2\xB0 08' 09'' 334'''";
//std::string res3 = "48\xC2\xB0 9' 10'' 334'''";
std::string res4 = "44\xC2\xB0 44' 45'' 776'''";
std::string zero = "0\xC2\xB0 00' 00'' 000'''";
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_01)
{
    BOOST_CHECK_EQUAL((x1 - x2).to_string(show_milliseconds), res2 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_02)
{
    BOOST_CHECK_EQUAL((x1 - x3).to_string(show_milliseconds), res1 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_03)
{
    BOOST_CHECK_EQUAL((x1 - x4).to_string(show_milliseconds), res3 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_04)
{
    BOOST_CHECK_EQUAL((x2 - x4).to_string(show_milliseconds), res1 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_05)
{
    BOOST_CHECK_EQUAL((x3 - x4).to_string(show_milliseconds), res2 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_06)
{
    BOOST_CHECK_EQUAL((x3 - x2).to_string(show_milliseconds), res4 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_07)
{
    BOOST_CHECK_EQUAL((x3 - x1).to_string(show_milliseconds), res1 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_08)
{
    BOOST_CHECK_EQUAL((x4 - x2).to_string(show_milliseconds), res1 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_09)
{
    BOOST_CHECK_EQUAL((x2 - x1).to_string(show_milliseconds), res2 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_10)
{
    BOOST_CHECK_EQUAL((x2 - x3).to_string(show_milliseconds), res4 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_11)
{
    BOOST_CHECK_EQUAL((x4 - x1).to_string(show_milliseconds), res3 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_12)
{
    BOOST_CHECK_EQUAL((x4 - x3).to_string(show_milliseconds), res2 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_sub_degree_13)
{
    BOOST_CHECK_EQUAL((x1 - x1).to_string(show_milliseconds), zero);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
