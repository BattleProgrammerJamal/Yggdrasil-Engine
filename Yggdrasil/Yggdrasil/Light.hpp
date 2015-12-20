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
#define SHADOW_MAP_WIDTH 64
#define SHADOW_MAP_HEIGHT 64
#define SHADOW_MAP_DEFAULT_ATTACHEMENT 0

namespace YG
{
	namespace Core
	{
		class Light
		{
			public:
				glm::mat4 shadowMapView;
				glm::mat4 shadowMapProj;

				Math::Vector3 position;
				Math::Color reflectance;
				float intensity;

				Light(Math::Vector3 position = Math::Vector3(), Math::Color reflectance = Math::Color(1.0f, 1.0f, 1.0f), float intensity = 1.0f, unsigned int shadowMapAttachement = SHADOW_MAP_DEFAULT_ATTACHEMENT, Shader *shadowMapShader = new Shader("Assets/shaders/shadowMap.vs", "Assets/shaders/shadowMap.fs"))
				{
					this->position = position;
					this->reflectance = reflectance;
					this->intensity = intensity;
					this->m_shadowMapShader = shadowMapShader;
					this->shadowMapView = glm::mat4(1.0f);
					this->shadowMapProj = glm::mat4(1.0f);
				}

				bool isCastShadow() const { return m_castShadow; }
				void setCastShadow(bool state) { m_castShadow = state; }

				Shader* getShadowMapShader() const { return m_shadowMapShader; }
				void setShadowMapShader(Shader* shader) { m_shadowMapShader = shader; }

			protected:
				bool m_castShadow;
				Shader* m_shadowMapShader;
		};
	};
};

#endif