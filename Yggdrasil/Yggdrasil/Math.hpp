#ifndef YGGDRASIL_MATH_HPP
#define YGGDRASIL_MATH_HPP

#include <iostream>
#include <cmath>

#define PI 3.1459f

namespace YG
{
	namespace Math
	{
		static float Rad(float angle)
		{
			return angle * PI / 180.0f;
		}

		static float Deg(float angle)
		{
			return angle * 180.0f / PI;
		}
	};
};

#endif