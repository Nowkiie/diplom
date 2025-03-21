#include <boost/test/unit_test.hpp>
#include <cmath>
#include "Degree.hpp"
BOOST_AUTO_TEST_SUITE(Longitude)
BOOST_AUTO_TEST_SUITE(ConstructAndConvertLongitude)
using namespace earth_math;
BOOST_AUTO_TEST_CASE(test_write_negative_double_value)
{
    degree_longitude firstDegree = degree_longitude::from_degree(-0.5);
    BOOST_CHECK_EQUAL(firstDegree.to_string(show_seconds),
                      "0\xC2\xB0 30' 00'' з.д.");
}

BOOST_AUTO_TEST_CASE(test_write_negative_near_zero_value)
{
    degree_longitude firstDegree(0, 0, 0, 256);
    degree_longitude secondDegree(0, 0, 0, 256, true);
    auto len = firstDegree.to_string(show_seconds).length();
    BOOST_CHECK_EQUAL(firstDegree.to_string(show_seconds).substr(0, len - 4),
                      secondDegree.to_string(show_seconds).substr(0, len - 4));
}
BOOST_AUTO_TEST_CASE(test_negative_double_string_value)
{
    degree_longitude firstDegree =
        degree_longitude::from_degree(0.0578964213456);
    degree_longitude secondDegree =
        degree_longitude::from_degree(-0.0578964213456);
    auto len = firstDegree.to_string(show_seconds).length();
    BOOST_CHECK_EQUAL(firstDegree.to_string(show_seconds).substr(0, len - 4),
                      secondDegree.to_string(show_seconds).substr(0, len - 4));
}
BOOST_AUTO_TEST_CASE(test_negative_double_value)
{
    degree_longitude firstDegree =
        degree_longitude::from_degree(17.578964213456);
    degree_longitude secondDegree =
        degree_longitude::from_degree(-17.578964213456);
    BOOST_CHECK_EQUAL(firstDegree.to_degree(), fabs(secondDegree.to_degree()));
}
BOOST_AUTO_TEST_CASE(test_negative_double_value_string_compare)
{
    degree_longitude firstDegree =
        degree_longitude::from_degree(17.578964213456);
    degree_longitude secondDegree =
        degree_longitude::from_degree(-17.578964213456);
    auto len = firstDegree.to_string(show_milliseconds).length();
    BOOST_CHECK_EQUAL(
        firstDegree.to_string(show_milliseconds).substr(0, len - 4),
        secondDegree.to_string(show_milliseconds).substr(0, len - 4));
}

BOOST_AUTO_TEST_CASE(test_convert_degree_in_int)
{
    degree_longitude startDegree(44, 35, 33, 127);
    degree_longitude convertDegreeAbstract =
        degree_longitude::from_degree(startDegree.to_degree());
    for (int32_t i = 0; i < 10000; i++)
    {
        degree_longitude tmpDeg =
            degree_longitude::from_degree(convertDegreeAbstract.to_degree());
        convertDegreeAbstract = tmpDeg;
    }
    BOOST_CHECK_EQUAL(startDegree, convertDegreeAbstract);
}
BOOST_AUTO_TEST_CASE(test_convert_degree_in_double)
{
    degree_longitude startDegree =
        degree_longitude::from_degree(44.578964213456);
    degree_longitude convertDegreeAbstract =
        degree_longitude::from_degree(startDegree.to_degree());
    for (int32_t i = 0; i < 10000; i++)
    {
        degree_longitude tmpDeg =
            degree_longitude::from_degree(convertDegreeAbstract.to_degree());
        convertDegreeAbstract = tmpDeg;
    }
    BOOST_CHECK_EQUAL(startDegree, convertDegreeAbstract);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
