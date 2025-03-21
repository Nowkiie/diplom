#include <boost/test/unit_test.hpp>
#include "earth_functions.hpp"
BOOST_AUTO_TEST_SUITE(FunctionalTests)
BOOST_AUTO_TEST_SUITE(PelengIntersectionTests)
using namespace earth_math;
BOOST_AUTO_TEST_CASE(test_peleng_intersection_01)
{
    earth_point p1(0., 0.);
    degree_abstract az1 = degree_abstract::from_degree(90.);
    earth_point p2(20., 120.);
    degree_abstract az2 = degree_abstract::from_degree(180.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 00' 120\xC2\xB0 00' в.д.";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_02)
{
    earth_point p1(0., 0.);
    degree_abstract az1 = degree_abstract::from_degree(90.);
    earth_point p2(20., 120.);
    degree_abstract az2 = degree_abstract::from_degree(0.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 00' 120\xC2\xB0 00' в.д.";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    //res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, false);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_03)
{
    earth_point p1(0., 0.);
    degree_abstract az1 = degree_abstract::from_degree(270.);
    earth_point p2(20., 180.);
    degree_abstract az2 = degree_abstract::from_degree(180.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 00' 180\xC2\xB0 00' з.д.";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_04)
{
    earth_point p1(0., 0.);
    degree_abstract az1 = degree_abstract::from_degree(90);
    earth_point p2(20., 180.);
    degree_abstract az2 = degree_abstract::from_degree(180.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 00' 180\xC2\xB0 00' в.д.";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_05)
{
    earth_point p1(0., 0.);
    degree_abstract az1 = degree_abstract::from_degree(90);
    earth_point p2(-20., 180.);
    degree_abstract az2 = degree_abstract::from_degree(180.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 00' 0\xC2\xB0 00'";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_06)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point res_point;
    earth_point target_point{55.4703, 107.649};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_07)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point p3(53.1167, 158.817);
    degree_abstract az3 = degree_abstract::from_degree(20.);
    earth_point p4(52.5333, 85.2);
    degree_abstract az4 = degree_abstract::from_degree(10.);
    earth_point res_point;
    earth_point target_point{60.7584, 88.1709};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p2, az2, p4, az4, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_08)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point p3(53.1167, 158.817);
    degree_abstract az3 = degree_abstract::from_degree(20.);
    earth_point p4(52.5333, 85.2);
    degree_abstract az4 = degree_abstract::from_degree(10.);
    earth_point res_point;
    earth_point target_point{70.6723, 179.312};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p1, az1, p3, az3, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_09)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point p3(53.1167, 158.817);
    degree_abstract az3 = degree_abstract::from_degree(20.);
    earth_point p4(52.5333, 85.2);
    degree_abstract az4 = degree_abstract::from_degree(10.);
    earth_point res_point;
    earth_point target_point{78.0988, -133.033};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p3, az3, p4, az4, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_10)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point p3(53.1167, 158.817);
    degree_abstract az3 = degree_abstract::from_degree(20.);
    earth_point p4(52.5333, 85.2);
    degree_abstract az4 = degree_abstract::from_degree(10.);
    earth_point res_point;
    earth_point target_point{1.94229, -102.973};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p1, az1, p4, az4, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_11)
{
    earth_point p1(52.1833, 103.967);
    degree_abstract az1 = degree_abstract::from_degree(32.);
    earth_point p2(52.8333, 113.483);
    degree_abstract az2 = degree_abstract::from_degree(310.);
    earth_point p3(53.1167, 158.817);
    degree_abstract az3 = degree_abstract::from_degree(20.);
    earth_point p4(52.5333, 85.2);
    degree_abstract az4 = degree_abstract::from_degree(10.);
    earth_point res_point;
    earth_point target_point{-18.9065, -33.2954};
    std::string target_res_str = target_point.to_string();
    bool res = peleng_intersection(p2, az2, p3, az3, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_12)
{
    earth_point p1(-50., -170.);
    degree_abstract az1 = degree_abstract::from_degree(90);
    earth_point p2(-20., 180.);
    degree_abstract az2 = degree_abstract::from_degree(180.);
    earth_point res_point;
    std::string target_res_str = "0\xC2\xB0 0' 0\xC2\xB0 0'";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    // res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, false);
}
BOOST_AUTO_TEST_CASE(test_peleng_intersection_13)
{
    earth_point p1(-50., -170.);
    degree_abstract az1 = degree_abstract::from_degree(90.);
    earth_point p2(-20., 180.);
    degree_abstract az2 = degree_abstract::from_degree(0.);
    earth_point res_point;
    std::string target_res_str = "49\xC2\xB0 34' с.ш. 0\xC2\xB0 00' в.д.";
    bool res = peleng_intersection(p1, az1, p2, az2, &res_point);
    std::string receive_res_str = res_point.to_string();
    res &= (target_res_str == receive_res_str);
    BOOST_CHECK_EQUAL(res, true);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
