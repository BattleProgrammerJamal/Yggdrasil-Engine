#ifndef YGGDRASIL_POINT_LIGHT_HPP
#define YGGDRASIL_POINT_LIGHT_HPP

#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Color.hpp"
#include "Light.hpp"

namespace YG
{
	namespace Core
	{
		struct LightAttenuation
		{
			float constant;
			float linear;
			float exponential;
		};

		class PointLight : public Light
		{
			public:
				LightAttenuation attenuation;

				PointLight(Math::Vector3 position = Math::Vector3(), Math::Color reflectance = Math::Color(1.0f, 1.0f, 1.0f), float intensity = 1.0f)
					: Light(position, reflectance, intensity)
				{
					type = POINT;
					attenuation.constant = 1.0f;
					attenuation.linear = 0.14f;
					attenuation.exponential = 0.07f;
				}
		};
	};
};

#endif