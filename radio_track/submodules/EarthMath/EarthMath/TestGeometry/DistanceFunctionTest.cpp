#include <boost/test/unit_test.hpp>
#include "earth_functions.hpp"
BOOST_AUTO_TEST_SUITE(FunctionalTests)
BOOST_AUTO_TEST_SUITE(DistanceTests)
using namespace earth_math;

std::string res1 = "90\xC2\xB0 00'";
std::string res2 = "180\xC2\xB0 00'";
std::string res3 = "179\xC2\xB0 00'";
std::string res5 = "1\xC2\xB0 00'";
std::string res6 = "0\xC2\xB0 00' 01'' 000'''";
std::string res7 = "0\xC2\xB0 00' 00'' 500'''";
std::string res8 = "0\xC2\xB0 00' 03'' 000'''";
double res10 = earth_radius * 2. * pi / 4.;
double res11 = earth_radius * pi;
std::string res12 = "135\xC2\xB0 00'";
//std::string res2 = "0\xC2\xB0 5' ю.ш. 0\xC2\xB0 5' з.д.";
BOOST_AUTO_TEST_CASE(test_distance_01)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(0., 0.), earth_point(50., 90.)).to_string(), res1);
}
BOOST_AUTO_TEST_CASE(test_distance_02)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(0., 90.), earth_point(0., 0.)).to_string(), res1);
}
BOOST_AUTO_TEST_CASE(test_distance_03)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(0., 90.), earth_point(0., -90.)).to_string(),
        res2);
}
BOOST_AUTO_TEST_CASE(test_distance_04)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(90., 20.), earth_point(-89., 20.)).to_string(),
        res3);
}
BOOST_AUTO_TEST_CASE(test_distance_05)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(-90., 20.), earth_point(-89., 20.)).to_string(),
        res5);
}
BOOST_AUTO_TEST_CASE(test_distance_06)
{
    BOOST_CHECK_EQUAL(distance(earth_point{int64_t(0), int64_t(1000)},
                               earth_point{int64_t(0), int64_t(2000)})
                          .to_string(show_milliseconds),
                      res6);
}
BOOST_AUTO_TEST_CASE(test_distance_07)
{
    BOOST_CHECK_EQUAL(distance(earth_point{int64_t(0), int64_t(1000)},
                               earth_point{int64_t(0), int64_t(1500)})
                          .to_string(show_milliseconds),
                      res7);
}
BOOST_AUTO_TEST_CASE(test_distance_08)
{
    BOOST_CHECK_EQUAL(distance(earth_point{int64_t(0), int64_t(-1500)},
                               earth_point{int64_t(0), int64_t(1500)})
                          .to_string(show_milliseconds),
                      res8);
}
BOOST_AUTO_TEST_CASE(test_distance_09)
{
    BOOST_CHECK_EQUAL(distance(earth_point{int64_t(-1500), int64_t(0)},
                               earth_point{int64_t(1500), int64_t(0)})
                          .to_string(show_milliseconds),
                      res8);
}
BOOST_AUTO_TEST_CASE(test_distance_10)
{
    BOOST_CHECK_EQUAL(
        distance_in_km(earth_point(0., 0.), earth_point(50., 90.)), res10);
}
BOOST_AUTO_TEST_CASE(test_distance_11)
{
    BOOST_CHECK_EQUAL(
        distance_in_km(earth_point(0., 90.), earth_point(0., -90.)), res11);
}
BOOST_AUTO_TEST_CASE(test_distance_12)
{
    BOOST_CHECK_EQUAL(
        distance(earth_point(0., 45.), earth_point(0., -90.)).to_string(),
        res12);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
