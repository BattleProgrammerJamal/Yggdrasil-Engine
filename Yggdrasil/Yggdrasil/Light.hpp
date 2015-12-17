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
				GLuint shadowMap;
				GLuint shadowMapFBO;
				GLuint shadowMapRBO;

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
					initShadowMap(shadowMapAttachement);
				}

				void initShadowMap(unsigned int attachement = 0)
				{
					glGenFramebuffers(1, &shadowMapFBO);
					glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);

					glGenRenderbuffers(1, &shadowMapRBO);
					glBindRenderbuffer(GL_RENDERBUFFER, shadowMapRBO);
					glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);

					glGenTextures(1, &shadowMap);
					glBindTexture(GL_TEXTURE_2D, shadowMap);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
					glBindTexture(GL_TEXTURE_2D, 0);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachement, GL_TEXTURE_2D, shadowMap, 0);

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					{
						std::cerr << "Error FrameBuffer : Unable to initialize Shadow Map data ..." << std::endl;
					}

					glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowMapRBO);

					glBindRenderbuffer(GL_RENDERBUFFER, 0);
					glBindFramebuffer(GL_FRAMEBUFFER, 0);
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