#ifndef YGGDRASIL_RENDERER_HPP
#define YGGDRASIL_RENDERER_HPP

#include <iostream>
#include <string>
#include <strstream>
#include <sstream>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "RenderTarget.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 3

#define MAXIMUM_LIGHT 16

#define UBO_SUPPORTED true
#define UBO_SIZE() sizeof(float) * (16 + 16 + 16)

namespace YG
{
	namespace Core
	{
		class Renderer
		{
			public:
				sf::Clock clock;
				float deltaTime;

				Renderer(unsigned int width = 800, unsigned int height = 600, const std::string& title = std::string("OpenGLRenderer"));
				virtual ~Renderer();

				bool render(Scene *scene, Camera *camera);

				unsigned int getWidth() const { return m_width; }
				void setWidth(unsigned int width) { m_width = width; }

				unsigned int getHeight() const { return m_height; }
				void setHeight(unsigned int height) { m_height = height; }

				sf::Window* getWindow() const { return m_window; }

				bool isFullscreen() { return m_fullscreen; }
				void setFullscreen(bool fullscreen) { m_fullscreen = fullscreen; createDisplay(); }
				void toggleFullscreen() { m_fullscreen = !m_fullscreen; createDisplay(); }

				Math::Color getClearColor() const { return m_clearColor; }
				void setClearColor(const Math::Color& color) { m_clearColor = color; }

				void setAlphaChannel(bool state)
				{
					if (state)
					{
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					}
					else
					{
						glDisable(GL_BLEND);
					}
				}

				GLuint getUBO() const { return m_ubo; }

				Renderer& addLight(Light *light)
				{
					m_lights[m_currentLightIndex] = light;
					m_currentLightIndex = (m_currentLightIndex + 1) % MAXIMUM_LIGHT;
					return *this;
				}

				Light& getLight(unsigned int index)
				{
					return *m_lights[index % MAXIMUM_LIGHT];
				}

			protected:
				void createDisplay(const std::string& title = "OpenGLRenderer");

				Shader *shadowMapShader;
				RenderTarget *shadowMap;
				GLuint m_ubo;
				sf::Window* m_window;
				sf::Event m_event;
				unsigned int m_width;
				unsigned int m_height;
				bool m_fullscreen;
				Math::Color m_clearColor;
				int m_currentLightIndex;
				Light* m_lights[MAXIMUM_LIGHT];
		};
	};
};

#endif