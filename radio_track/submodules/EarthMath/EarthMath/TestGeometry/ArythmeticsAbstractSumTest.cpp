#include <boost/test/unit_test.hpp>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Abstract)
BOOST_AUTO_TEST_SUITE(ArythmeticsAbstractSum)
using namespace earth_math;
degree_abstract x1(155, 55, 55, 333, true);
degree_abstract x2(22, 22, 22, 888, true);
degree_abstract x3(22, 22, 22, 888);
degree_abstract x4(155, 55, 55, 333);
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_01)
{
    BOOST_CHECK_EQUAL((x1 + x2).to_string(show_milliseconds),
                      "-178\xC2\xB0 18' 18'' 221'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_02)
{
    BOOST_CHECK_EQUAL((x1 + x3).to_string(show_milliseconds),
                      "-133\xC2\xB0 33' 32'' 445'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_03)
{
    BOOST_CHECK_EQUAL((x1 + x4).to_string(show_milliseconds),
                      "0\xC2\xB0 00' 00'' 000'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_04)
{
    BOOST_CHECK_EQUAL((x2 + x4).to_string(show_milliseconds),
                      "133\xC2\xB0 33' 32'' 445'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_05)
{
    BOOST_CHECK_EQUAL((x3 + x4).to_string(show_milliseconds),
                      "178\xC2\xB0 18' 18'' 221'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_06)
{
    BOOST_CHECK_EQUAL((x3 + x2).to_string(show_milliseconds),
                      "0\xC2\xB0 00' 00'' 000'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_07)
{
    BOOST_CHECK_EQUAL((x3 + x1).to_string(show_milliseconds),
                      "-133\xC2\xB0 33' 32'' 445'''");
}
BOOST_AUTO_TEST_CASE(test_arythm_sum_degree_08)
{
    BOOST_CHECK_EQUAL((x4 + x2).to_string(show_milliseconds),
                      "133\xC2\xB0 33' 32'' 445'''");
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
