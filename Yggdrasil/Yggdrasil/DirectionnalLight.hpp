#ifndef YGGDRASIL_DIRECTIONNAL_LIGHT_HPP
#define YGGDRASIL_DIRECTIONNAL_LIGHT_HPP

#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Color.hpp"
#include "Light.hpp"

namespace YG
{
	namespace Core
	{
		class DirectionnalLight : public Light
		{
			public:
				Math::Vector3 direction;

				DirectionnalLight(Math::Vector3 position = Math::Vector3(), Math::Vector3 direction = Math::Vector3(), Math::Color reflectance = Math::Color(1.0f, 1.0f, 1.0f), float intensity = 1.0f)
					: Light(position, reflectance, intensity)
				{
					type = DIRECTIONNAL;
					this->direction = direction;
				}

		};
	};
};

#endif