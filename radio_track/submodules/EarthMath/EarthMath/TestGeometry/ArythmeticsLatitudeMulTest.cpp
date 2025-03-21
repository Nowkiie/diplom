#include <boost/test/unit_test.hpp>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Latitude)
BOOST_AUTO_TEST_SUITE(ArythmeticsLatitudeMul)
using namespace earth_math;
degree_latitude x1(75, 55, 55, 333, true);
degree_latitude x2(22, 22, 22, 888, true);
degree_latitude x3(22, 22, 22, 888);
degree_latitude x4(75, 55, 55, 333);
std::string res1 = "37\xC2\xB0 57' 57'' 666'''";
std::string res2 = "28\xC2\xB0 08' 09'' 334'''";
std::string res3 = "11\xC2\xB0 11' 11'' 444'''";
std::string res4 = "44\xC2\xB0 44' 45'' 776'''";
std::string res5 = "67\xC2\xB0 27' 22'' 664'''";
std::string res6 = "9\xC2\xB0 29' 29'' 416'''";
std::string zero = "0\xC2\xB0 00' 00'' 000'''";
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_01)
{
    BOOST_CHECK_EQUAL((x1 * 0.5).to_string(show_milliseconds), res1 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_02)
{
    BOOST_CHECK_EQUAL((x1 * 2).to_string(show_milliseconds), res2 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_03)
{
    BOOST_CHECK_EQUAL((x2 * 0.5).to_string(show_milliseconds), res3 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_04)
{
    BOOST_CHECK_EQUAL((x2 * 2).to_string(show_milliseconds), res4 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_05)
{
    BOOST_CHECK_EQUAL((x1 * 0).to_string(show_milliseconds), zero);
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_06)
{
    BOOST_CHECK_EQUAL((x4 * 0.5).to_string(show_milliseconds), res1 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_07)
{
    BOOST_CHECK_EQUAL((x4 * 2).to_string(show_milliseconds), res2 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_08)
{
    BOOST_CHECK_EQUAL((x3 * 0.5).to_string(show_milliseconds), res3 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_09)
{
    BOOST_CHECK_EQUAL((x3 * 2).to_string(show_milliseconds), res4 + " с.ш.");
}

BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_10)
{
    BOOST_CHECK_EQUAL((x4 * 0).to_string(show_milliseconds), zero);
}

BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_11)
{
    BOOST_CHECK_EQUAL((x4 * 8).to_string(show_milliseconds), res5 + " ю.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_12)
{
    BOOST_CHECK_EQUAL((x1 * 8).to_string(show_milliseconds), res5 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_13)
{
    BOOST_CHECK_EQUAL((x4 * 0.125).to_string(show_milliseconds),
                      res6 + " с.ш.");
}
BOOST_AUTO_TEST_CASE(test_arythm_mul_degree_14)
{
    BOOST_CHECK_EQUAL((x1 * 0.125).to_string(show_milliseconds),
                      res6 + " ю.ш.");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
