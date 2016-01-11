#ifndef YGGDRASIL_LIGHT_HPP
#define YGGDRASIL_LIGHT_HPP

#include <iostream>
#include <vector>
#include "Vector3.hpp"
#include "Color.hpp"
#include "Shader.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#define LIGHT_SIZE() sizeof(float) * (3 + 3 + 1)

namespace YG
{
	namespace Core
	{
		enum LIGHT_TYPE
		{
			DIRECTIONNAL = 0,
			POINT,
			SPOT
		};

		class Light
		{
			public:
				Math::Vector3 position;
				Math::Color reflectance;
				float intensity;
				bool showGizmo;
				LIGHT_TYPE type;

				Light(Math::Vector3 position = Math::Vector3(), Math::Color reflectance = Math::Color(1.0f, 1.0f, 1.0f), float intensity = 1.0f)
				{
					this->position = position;
					this->reflectance = reflectance;
					this->intensity = intensity;
					this->showGizmo = false;
					this->type = DIRECTIONNAL;
				}

				bool isCastShadow() const { return m_castShadow; }
				void setCastShadow(bool state) { m_castShadow = state; }

			protected:
				bool m_castShadow;
		};
	};
};

#endif