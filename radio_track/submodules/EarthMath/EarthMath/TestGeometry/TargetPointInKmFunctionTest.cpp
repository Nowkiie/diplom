#include <boost/test/unit_test.hpp>
#include "earth_functions.hpp"
BOOST_AUTO_TEST_SUITE(FunctionalTests)
BOOST_AUTO_TEST_SUITE(TargetPointInKmTests)
using namespace earth_math;
std::string res1 = "2\xC2\xB0 21' ю.ш. 161\xC2\xB0 32' в.д.";
BOOST_AUTO_TEST_CASE(test_target_01)
{
	earth_point st(-289980,-220800);
	BOOST_CHECK_EQUAL(
		target_point(st, degree_abstract::from_degree(223.003), 10514.8)
		.to_string(),
		res1);
}
BOOST_AUTO_TEST_CASE(test_target_02)
{
	double e = 1e-4;
	earth_point st(-45., -45.);
	double t_az = 45.;
	double t_len = 12000.;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	bool res = false;
	if (((fabs(az - t_az) < eps) && (fabs(t_len - len) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_CASE(test_target_03)
{
	double e = 1e-4;
	earth_point st(-6900, -246780);
	double t_az = 185.291;
	double t_len = 13001.7;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	earth_point testp(-218520, 436020);
	double az1 = azimuth(st, testp).to_degree();
	double len1 = distance_in_km(st, testp);
	bool res = false;
	if (((fabs(az - t_az) < eps) && (fabs(t_len - len) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_CASE(test_target_04)
{
	double e = 1e-4;
	earth_point st(-50., -120.);
	double t_az = 45.;
	double t_len = earth_radius*3;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	earth_point testp(-218520, 436020);
	double az1 = azimuth(st, testp).to_degree();
	double len1 = distance_in_km(st, testp);
	bool res = false;
	if (((fabs(az - t_az) < e) && (fabs(t_len - len) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_CASE(test_target_05)
{
	double e = 1e-4;
	earth_point st(-50., -120.);
	double t_az = 45.;
	double t_len = earth_radius * 7;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	earth_point testp(-218520, 436020);
	double az1 = azimuth(st, testp).to_degree();
	double len1 = distance_in_km(st, testp);
	bool res = false;
	if (((fabs(az - t_az) < e) && (fabs(t_len - len-2*pi*earth_radius) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_CASE(test_target_06)
{
	double e = 1e-4;
	earth_point st(-50., -120.);
	double t_az = 195;
	double t_len = earth_radius * 10;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	earth_point testp(-218520, 436020);
	double az1 = azimuth(st, testp).to_degree();
	double len1 = distance_in_km(st, testp);
	bool res = false;
	std::string endps = endp.to_string();
	double res1 = az + 180 - t_az;
	double l = 2 * pi*earth_radius - len;
	double res2 = t_len - l - 2 * pi*earth_radius;
	if (((fabs(az + 180 - t_az) < e) && (fabs(t_len - l - 2 * pi*earth_radius) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_CASE(test_target_07)
{
	double e = 1e-4;
	earth_point st(198240, 345480);
	earth_point st2(-161700, -530340);
	double testLen = distance_in_km(st, st2);
	double t_az = 102.766272559;
	double t_len = 15519.06753;
	earth_point endp = 
		target_point(st, degree_abstract::from_degree(t_az), t_len);
	double az = azimuth(st, endp).to_degree();
	double len = distance_in_km(st, endp);
	std::string endps = endp.to_string();
	bool res = false;
	if (((fabs(az - t_az) < e) && (fabs(t_len - len) < e)))
		res = true;
	BOOST_CHECK_EQUAL(res,
		true);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()