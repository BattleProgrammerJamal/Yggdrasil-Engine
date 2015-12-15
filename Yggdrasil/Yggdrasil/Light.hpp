#ifndef YGGDRASIL_LIGHT_HPP
#define YGGDRASIL_LIGHT_HPP

#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Color.hpp"

#define LIGHT_SIZE() sizeof(float) * (3 + 3 + 1)

namespace YG
{
	namespace Core
	{
		class Light
		{
			public:
				Math::Vector3 position;
				Math::Color reflectance;
				float intensity;

				Light(Math::Vector3 position = Math::Vector3(), Math::Color reflectance = Math::Color(1.0f, 1.0f, 1.0f), float intensity = 1.0f)
				{
					this->position = position;
					this->reflectance = reflectance;
					this->intensity = intensity;
				}
		};
	};
};

#endif