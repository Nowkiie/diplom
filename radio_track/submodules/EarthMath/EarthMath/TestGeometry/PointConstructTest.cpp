#include <boost/test/unit_test.hpp>
#include "earth_point.hpp"
BOOST_AUTO_TEST_SUITE(PointConstruct)
using namespace earth_math;
double x1 = 58.582983;
double y1 = 49.660516;
int32_t x2 = -300;
int32_t y2 = -300;
int64_t x3 = -300000;
int64_t y3 = -300000;
std::string res1 = "58\xC2\xB0 34' с.ш. 49\xC2\xB0 39' в.д.";
std::string res2 = "0\xC2\xB0 05' ю.ш. 0\xC2\xB0 05' з.д.";
BOOST_AUTO_TEST_CASE(test_construct_point_01)
{
    earth_point p{degree_latitude::from_degree(x1),
                  degree_longitude::from_degree(y1)};
    std::string res = p.to_string(show_minutes);
    BOOST_CHECK_EQUAL(res, res1);
}
BOOST_AUTO_TEST_CASE(test_construct_point_02)
{
    earth_point p(x1, y1);
    std::string res = p.to_string(show_minutes);
    BOOST_CHECK_EQUAL(res, res1);
}
BOOST_AUTO_TEST_CASE(test_construct_point_03)
{
    earth_point p(x2, y2);
    std::string res = p.to_string(show_minutes);
    BOOST_CHECK_EQUAL(res, res2);
}
BOOST_AUTO_TEST_CASE(test_construct_point_04)
{
    earth_point p(x3, y3);
    std::string res = p.to_string(show_minutes);
    BOOST_CHECK_EQUAL(res, res2);
}
BOOST_AUTO_TEST_CASE(test_construct_point_05)
{
    earth_point p;
    p.set_latitude(degree_latitude::from_milliseconds(x3));
    p.set_longitude(degree_longitude::from_milliseconds(y3));
    std::string res = p.to_string(show_minutes);
    BOOST_CHECK_EQUAL(res, res2);
}
BOOST_AUTO_TEST_SUITE_END()
