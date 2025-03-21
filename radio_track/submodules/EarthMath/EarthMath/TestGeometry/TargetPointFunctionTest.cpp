#include <boost/test/unit_test.hpp>
#include "earth_functions.hpp"
BOOST_AUTO_TEST_SUITE(FunctionalTests)
BOOST_AUTO_TEST_SUITE(TargetPointTests)
using namespace earth_math;
std::string res1 = "0\xC2\xB0 00' 60\xC2\xB0 00' в.д.";
std::string res2 = "0\xC2\xB0 00' 40\xC2\xB0 00' з.д.";
std::string res3 = "0\xC2\xB0 00' 175\xC2\xB0 00' з.д.";
std::string res4 = "0\xC2\xB0 00' 15\xC2\xB0 00' в.д.";
std::string res8 = "0\xC2\xB0 00' 10\xC2\xB0 00' в.д.";
std::string res9 = "45\xC2\xB0 00' с.ш. 45\xC2\xB0 00' в.д.";
std::string res10 = "90\xC2\xB0 00' с.ш. 45\xC2\xB0 00' в.д.";
std::string res11 = "45\xC2\xB0 00' с.ш. 135\xC2\xB0 00' з.д.";
std::string res12 = "0\xC2\xB0 00' 135\xC2\xB0 00' з.д.";
std::string res13 = "45\xC2\xB0 00' ю.ш. 135\xC2\xB0 00' з.д.";
std::string res14 = "90\xC2\xB0 00' ю.ш. 45\xC2\xB0 00' в.д.";
std::string res15 = "45\xC2\xB0 00' ю.ш. 45\xC2\xB0 00' в.д.";

std::string res16 = "90\xC2\xB0 00' ю.ш. 45\xC2\xB0 00' з.д.";
std::string res17 = "45\xC2\xB0 00' ю.ш. 135\xC2\xB0 00' в.д.";
std::string res18 = "0\xC2\xB0 00' 135\xC2\xB0 00' в.д.";
std::string res19 = "45\xC2\xB0 00' с.ш. 135\xC2\xB0 00' в.д.";
std::string res20 = "90\xC2\xB0 00' с.ш. 45\xC2\xB0 00' з.д.";
std::string res21 = "45\xC2\xB0 00' с.ш. 45\xC2\xB0 00' з.д.";
std::string res22 = "0\xC2\xB0 00' 45\xC2\xB0 00' з.д.";
BOOST_AUTO_TEST_CASE(test_target_01)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(90.),
                                   degree_abstract::from_degree(50.))
                          .to_string(),
                      res1);
}
BOOST_AUTO_TEST_CASE(test_target_02)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(270.),
                                   degree_abstract::from_degree(50.))
                          .to_string(),
                      res2);
}
BOOST_AUTO_TEST_CASE(test_target_03)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(90.),
                                   degree_abstract::from_degree(175.))
                          .to_string(),
                      res3);
}
BOOST_AUTO_TEST_CASE(test_target_04)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(90.),
                                   degree_abstract::from_degree(365.))
                          .to_string(),
                      res4);
}
BOOST_AUTO_TEST_CASE(test_target_05)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(90.),
                                   degree_abstract::from_degree(895.))
                          .to_string(),
                      res3);
}
BOOST_AUTO_TEST_CASE(test_target_06)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(270.),
                                   degree_abstract::from_degree(905.))
                          .to_string(),
                      res3);
}
BOOST_AUTO_TEST_CASE(test_target_07)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(270.),
                                   degree_abstract::from_degree(-895.))
                          .to_string(),
                      res3);
}
BOOST_AUTO_TEST_CASE(test_target_08)
{
    earth_point st(0., 10.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(270.),
                                   degree_abstract::from_degree(0.))
                          .to_string(),
                      res8);
}
BOOST_AUTO_TEST_CASE(test_target_09)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(90.))
                          .to_string(),
                      res9);
}
BOOST_AUTO_TEST_CASE(test_target_10)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(135.))
                          .to_string(),
                      res10);
}
BOOST_AUTO_TEST_CASE(test_target_11)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(180.))
                          .to_string(),
                      res11);
}
BOOST_AUTO_TEST_CASE(test_target_12)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(225.))
                          .to_string(),
                      res12);
}
BOOST_AUTO_TEST_CASE(test_target_13)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(270.))
                          .to_string(),
                      res13);
}
BOOST_AUTO_TEST_CASE(test_target_14)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(315.))
                          .to_string(),
                      res14);
}
BOOST_AUTO_TEST_CASE(test_target_15)
{
    earth_point st(-45., 45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(0.),
                                   degree_abstract::from_degree(360.))
                          .to_string(),
                      res15);
}
BOOST_AUTO_TEST_CASE(test_target_16)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(45.))
                          .to_string(),
                      res16);
}
BOOST_AUTO_TEST_CASE(test_target_17)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(90.))
                          .to_string(),
                      res17);
}
BOOST_AUTO_TEST_CASE(test_target_18)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(135.))
                          .to_string(),
                      res18);
}
BOOST_AUTO_TEST_CASE(test_target_19)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(180.))
                          .to_string(),
                      res19);
}
BOOST_AUTO_TEST_CASE(test_target_20)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(225.))
                          .to_string(),
                      res20);
}
BOOST_AUTO_TEST_CASE(test_target_21)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(270.))
                          .to_string(),
                      res21);
}
BOOST_AUTO_TEST_CASE(test_target_22)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(315.))
                          .to_string(),
                      res22);
}
BOOST_AUTO_TEST_CASE(test_target_23)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(360.))
                          .to_string(),
                      target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(-360.))
                          .to_string());
}
BOOST_AUTO_TEST_CASE(test_target_24)
{
    earth_point st(-45., -45.);
    BOOST_CHECK_EQUAL(target_point(st, degree_abstract::from_degree(180.),
                                   degree_abstract::from_degree(0))
                          .to_string(),
                      st.to_string());
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
