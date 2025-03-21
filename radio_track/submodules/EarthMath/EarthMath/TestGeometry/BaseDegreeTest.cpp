#include <boost/test/unit_test.hpp>
#include <cmath>
#include "degree.hpp"
BOOST_AUTO_TEST_SUITE(Abstract)
BOOST_AUTO_TEST_SUITE(ConstructAndConvert)
using namespace earth_math;
BOOST_AUTO_TEST_CASE(test_write_negative_double_value)
{
    degree_abstract firstDegree = degree_abstract::from_degree(-0.5);
    BOOST_CHECK_EQUAL(firstDegree.to_string(show_seconds),
                      "-0\xC2\xB0 30' 00''");
}

BOOST_AUTO_TEST_CASE(test_write_negative_near_zero_value)
{
    degree_abstract firstDegree(0, 0, 0, 256);
    degree_abstract secondDegree(0, 0, 0, 256, true);
    BOOST_CHECK_EQUAL("-" + firstDegree.to_string(show_seconds),
                      secondDegree.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_negative_double_string_value)
{
    degree_abstract firstDegree = degree_abstract::from_degree(0.0578964213456);
    degree_abstract secondDegree =
        degree_abstract::from_degree(-0.0578964213456);
    BOOST_CHECK_EQUAL("-" + firstDegree.to_string(show_seconds),
                      secondDegree.to_string(show_seconds));
}
BOOST_AUTO_TEST_CASE(test_negative_double_value)
{
    degree_abstract firstDegree =
        degree_abstract::from_degree(170.578964213456);
    degree_abstract secondDegree =
        degree_abstract::from_degree(-170.578964213456);
    BOOST_CHECK_EQUAL(firstDegree.to_degree(), fabs(secondDegree.to_degree()));
}
BOOST_AUTO_TEST_CASE(test_negative_double_value_string_compare)
{
    degree_abstract firstDegree =
        degree_abstract::from_degree(170.578964213456);
    degree_abstract secondDegree =
        degree_abstract::from_degree(-170.578964213456);
    BOOST_CHECK_EQUAL("-" + firstDegree.to_string(show_milliseconds),
                      secondDegree.to_string(show_milliseconds));
}

BOOST_AUTO_TEST_CASE(test_convert_degree_in_int)
{
    degree_abstract startDegree(44, 35, 33, 127);
    degree_abstract convertDegreeAbstract =
        degree_abstract::from_degree(startDegree.to_degree());
    for (int32_t i = 0; i < 10000; i++)
    {
        degree_abstract tmpDeg =
            degree_abstract::from_degree(convertDegreeAbstract.to_degree());
        convertDegreeAbstract = tmpDeg;
    }
    BOOST_CHECK_EQUAL(startDegree, convertDegreeAbstract);
}
BOOST_AUTO_TEST_CASE(test_convert_degree_in_double)
{
    degree_abstract startDegree = degree_abstract::from_degree(44.578964213456);
    degree_abstract convertDegreeAbstract =
        degree_abstract::from_degree(startDegree.to_degree());
    for (int32_t i = 0; i < 10000; i++)
    {
        degree_abstract tmpDeg =
            degree_abstract::from_degree(convertDegreeAbstract.to_degree());
        convertDegreeAbstract = tmpDeg;
    }
    BOOST_CHECK_EQUAL(startDegree, convertDegreeAbstract);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
