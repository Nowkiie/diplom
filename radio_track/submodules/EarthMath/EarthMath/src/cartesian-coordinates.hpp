#pragma once
#include "earth_point.hpp"
#include "earth_functions.hpp"

namespace earth_math
{
	struct cartesian_point_t
	{
		cartesian_point_t()
			:x(0.0)
			,y(0.0)
			,z(0.0)
		{}
		
		// (0,0,0) - Earth Center
		double x; //на 90 градусов в.д. 0 широты, км
		double y; //на Северный Полюс, км
		double z; //на 0 с.ш. 0 в.д., км
	};

	static bool is_cartesian_point_convertable(
		const cartesian_point_t& c_point)
	{
		double control_value = 0.0;

		control_value += c_point.x * c_point.x;
		control_value += c_point.y * c_point.y;
		control_value += c_point.z * c_point.z;

		if (control_value < eps) return false;
		return true;
	}
	
	typedef std::vector<cartesian_point_t> cartesian_points_t;

	//географические -> декартовы
	static cartesian_point_t to_cartesian(
		const earth_point& point, double altitude = 0.0)
	{
		cartesian_point_t result;
		const double r = earth_radius + altitude;
		const double d = point.longitude().to_radians();
		const double s = point.latitude().to_radians();

		result.x = r * std::sin(pi / 2 - s)* std::sin(d);
		result.z = r * std::sin(pi / 2 - s)* std::cos(d);
		result.y = r * std::cos(pi / 2 - s);
		if (std::abs(result.x) < eps) result.x = 0.;
		if (std::abs(result.y) < eps) result.y = 0.;
		if (std::abs(result.z) < eps) result.z = 0.;

		return result;
	}

	//декартовы -> географические
	static earth_point to_geographical(
		const cartesian_point_t& point)
	{
		const double x = point.x;
		const double y = point.y;
		const double z = point.z;

		//неконвертируемая точка
		if (!is_cartesian_point_convertable(point))
		{
			return earth_point{};
		}
		
		double s = pi / 2 - std::acos(y / sqrt(x * x + y * y + z * z));
		double d = 0.;

		//if (abs(z) < eps) d = sign(x)*pi / 2;
		if (std::abs(z) < eps)
			d = (x < 0.0 ? -1.0 : x > 0.0 ? 1.0 : 0.0) * pi / 2;
		else
		{
			if ((z > 0.) && (x >= 0.)) d = std::atan(x / z);
			if ((z > 0.) && (x < 0.)) d = 2 * pi + std::atan(x / z);
			if (z < 0.) d = pi + std::atan(x / z);
		}

		if (d > pi) d = d - 2 * pi;
		if (std::abs(d) < eps) d = 0;
		if (std::abs(s) < eps) s = 0;

		earth_point result(
			degree_latitude::from_radians(s), 
			degree_longitude::from_radians(d));

		return result;
	}

	static double cartesian_range(const cartesian_point_t& p1, const cartesian_point_t& p2)
	{
		//расстояние между точками в декартовой СК
		double result = 0.;
		result += std::pow(p1.x - p2.x, 2);
		result += std::pow(p1.y - p2.y, 2);
		result += std::pow(p1.z - p2.z, 2);
		
		return(std::sqrt(result));
	}

	static cartesian_point_t cartesian_center(cartesian_points_t cPoints)
	{
		//геометрический центр набора точек
		cartesian_point_t result;
		const size_t pCount = cPoints.size();
		if (pCount == 0) return result;
			
		for (const cartesian_point_t& p : cPoints)
		{
			result.x += p.x;
			result.y += p.y;
			result.z += p.z;
		}

		result.x = result.x / pCount;
		result.y = result.y / pCount;
		result.z = result.z / pCount;

		return result;
	}
} //namespace earth_map
