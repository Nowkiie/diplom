#include <boost/test/unit_test.hpp>
#include "earth_functions.hpp"
BOOST_AUTO_TEST_SUITE(FunctionalTests)
BOOST_AUTO_TEST_SUITE(AzimuthTests)
using namespace earth_math;
std::string res1 = "40\xC2\xB0 00'";
std::string res2 = "140\xC2\xB0 00'";
std::string res3 = "320\xC2\xB0 00'";
std::string res4 = "0\xC2\xB0 00'";
std::string res5 = "180\xC2\xB0 00'";
std::string res7 = "90\xC2\xB0 00'";
std::string res8 = "270\xC2\xB0 00'";
BOOST_AUTO_TEST_CASE(test_azimuth_01)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., 0.), earth_point(50., 90.)).to_string(), res1);
}
BOOST_AUTO_TEST_CASE(test_azimuth_02)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., 30.), earth_point(-50., 120.)).to_string(),
        res2);
}
BOOST_AUTO_TEST_CASE(test_azimuth_03)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., 120.), earth_point(50., 30.)).to_string(),
        res3);
}
BOOST_AUTO_TEST_CASE(test_azimuth_04)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(-20., -38.), earth_point(85., -38.)).to_string(),
        res4);
}
BOOST_AUTO_TEST_CASE(test_azimuth_05)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(85., -38.), earth_point(-20., -38.)).to_string(),
        res5);
}
BOOST_AUTO_TEST_CASE(test_azimuth_06)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., -38.), earth_point(0., -38.)).to_string(),
        res4);
}
BOOST_AUTO_TEST_CASE(test_azimuth_07)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., -38.), earth_point(0., 50.)).to_string(), res7);
}
BOOST_AUTO_TEST_CASE(test_azimuth_08)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., -90.), earth_point(0., 170.)).to_string(),
        res8);
}
BOOST_AUTO_TEST_CASE(test_azimuth_09)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(0., -9.5), earth_point(0., 170.)).to_string(),
        res7);
}
BOOST_AUTO_TEST_CASE(test_azimuth_10)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(-45., -45.), earth_point(0., 0.)).to_string(),
        azimuth(earth_point(-45., -45.), earth_point(45., 45.)).to_string());
}
BOOST_AUTO_TEST_CASE(test_azimuth_11)
{
    BOOST_CHECK_EQUAL(
        azimuth(earth_point(-45., 45.), earth_point(0., 0.)).to_string(),
        azimuth(earth_point(-45., 45.), earth_point(45., -45.)).to_string());
}
BOOST_AUTO_TEST_CASE(test_azimuth_12)
{
    BOOST_CHECK_EQUAL(
        (azimuth(earth_point(0., -45.), earth_point(0., 45.))
         + degree_abstract::from_degree(180.))
            .to_string(),
        azimuth(earth_point(0., 45.), earth_point(0., -45.)).to_string());
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
