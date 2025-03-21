#include <boost/test/unit_test.hpp>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Longitude)
BOOST_AUTO_TEST_SUITE(ArythmeticsLongitudeMul)
using namespace earth_math;
degree_longitude x1(175, 55, 55, 333, true);
degree_longitude x2(22, 22, 22, 888, true);
degree_longitude x3(22, 22, 22, 888);
degree_longitude x4(175, 55, 55, 333);
std::string res1 = "87\xC2\xB0 57' 57'' 666'''";
std::string res2 = "8\xC2\xB0 08' 09'' 334'''";
std::string res3 = "11\xC2\xB0 11' 11'' 444'''";
std::string res4 = "44\xC2\xB0 44' 45'' 776'''";
std::string res5 = "32\xC2\xB0 32' 37'' 336'''";
std::string res6 = "21\xC2\xB0 59' 29'' 416'''";
std::string zero = "0\xC2\xB0 00' 00'' 000'''";
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_01)
{
    BOOST_CHECK_EQUAL((x1 * 0.5).to_string(show_milliseconds), res1 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_02)
{
    BOOST_CHECK_EQUAL((x1 * 2).to_string(show_milliseconds), res2 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_03)
{
    BOOST_CHECK_EQUAL((x2 * 0.5).to_string(show_milliseconds), res3 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_04)
{
    BOOST_CHECK_EQUAL((x2 * 2).to_string(show_milliseconds), res4 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_05)
{
    BOOST_CHECK_EQUAL((x1 * 0).to_string(show_milliseconds), zero);
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_06)
{
    BOOST_CHECK_EQUAL((x4 * 0.5).to_string(show_milliseconds), res1 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_07)
{
    BOOST_CHECK_EQUAL((x4 * 2).to_string(show_milliseconds), res2 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_08)
{
    BOOST_CHECK_EQUAL((x3 * 0.5).to_string(show_milliseconds), res3 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_09)
{
    BOOST_CHECK_EQUAL((x3 * 2).to_string(show_milliseconds), res4 + " в.д.");
}

BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_10)
{
    BOOST_CHECK_EQUAL((x4 * 0).to_string(show_milliseconds), zero);
}

BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_11)
{
    BOOST_CHECK_EQUAL((x4 * 8).to_string(show_milliseconds), res5 + " з.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_12)
{
    BOOST_CHECK_EQUAL((x1 * 8).to_string(show_milliseconds), res5 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_13)
{
    BOOST_CHECK_EQUAL((x4 * 0.125).to_string(show_milliseconds),
                      res6 + " в.д.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_14)
{
    BOOST_CHECK_EQUAL((x1 * 0.125).to_string(show_milliseconds),
                      res6 + " з.д.");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
