#include <boost/test/unit_test.hpp>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Abstract)
BOOST_AUTO_TEST_SUITE(ArythmeticsAbstractDiv)
using namespace earth_math;
degree_abstract x1(155, 55, 55, 333, true);
degree_abstract x2(22, 22, 22, 888, true);
degree_abstract x3(22, 22, 22, 888);
degree_abstract x4(155, 55, 55, 333);
std::string res1 = "11\xC2\xB0 11' 11'' 444'''";
std::string res2 = "77\xC2\xB0 57' 57'' 666'''";
std::string res3 = "311\xC2\xB0 51' 50'' 666'''";
std::string res4 = "44\xC2\xB0 44' 45'' 776'''";
std::string zero = "0\xC2\xB0 0' 0'' 0'''";
std::string res5 = "1247\xC2\xB0 27' 22'' 664'''";
std::string res6 = "19\xC2\xB0 29' 29'' 416'''";
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_01)
{
    BOOST_CHECK_EQUAL((x1 / 2).to_string(show_milliseconds), "-" + res2);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_02)
{
    BOOST_CHECK_EQUAL((x1 / 0.5).to_string(show_milliseconds), "-" + res3);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_03)
{
    BOOST_CHECK_EQUAL((x2 / 2).to_string(show_milliseconds), "-" + res1);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_04)
{
    BOOST_CHECK_EQUAL((x2 / 0.5).to_string(show_milliseconds), "-" + res4);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_05)
{
    BOOST_CHECK_EQUAL((x4 / 2).to_string(show_milliseconds), res2);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_06)
{
    BOOST_CHECK_EQUAL((x4 / 0.5).to_string(show_milliseconds), res3);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_07)
{
    BOOST_CHECK_EQUAL((x3 / 2).to_string(show_milliseconds), res1);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_08)
{
    BOOST_CHECK_EQUAL((x3 / 0.5).to_string(show_milliseconds), res4);
}

BOOST_AUTO_TEST_CASE(test_arythm_div_degree_09)
{
    BOOST_CHECK_EQUAL((x4 / 0.125).to_string(show_milliseconds), res5);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_10)
{
    BOOST_CHECK_EQUAL((x1 / 0.125).to_string(show_milliseconds), "-" + res5);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_13)
{
    BOOST_CHECK_EQUAL((x4 / 8).to_string(show_milliseconds), res6);
}
BOOST_AUTO_TEST_CASE(test_arythm_div_degree_14)
{
    BOOST_CHECK_EQUAL((x1 / 8).to_string(show_milliseconds), "-" + res6);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
