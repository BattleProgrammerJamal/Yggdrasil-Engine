#ifndef YGGDRASIL_RENDERER_HPP
#define YGGDRASIL_RENDERER_HPP

#include <iostream>
#include <string>
#include <strstream>
#include <sstream>
#include "Scene.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "DirectionnalLight.hpp"
#include "PointLight.hpp"
#include "RenderTarget.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 3
#define MAXIMUM_LIGHT 16

#define DEFAULT_POST_PROCESS_VS "Assets/shaders/postprocess.vs"
#define DEFAULT_POST_PROCESS_FS "Assets/shaders/postprocess.fs"
#define DEFAULT_POST_PROCESS_RT_WIDTH 1024
#define DEFAULT_POST_PROCESS_RT_HEIGHT 768

#define SHADOW_MAP_WIDTH 1024
#define SHADOW_MAP_HEIGHT 1024

#define DEFAULT_SKYBOX_VS "Assets/shaders/skybox.vs"
#define DEFAULT_SKYBOX_FS "Assets/shaders/skybox.fs"
#define DEFAULT_SKYBOX2_TOP "Assets/textures/skybox/top.jpg"
#define DEFAULT_SKYBOX2_BOTTOM "Assets/textures/skybox/bottom.jpg"
#define DEFAULT_SKYBOX2_LEFT "Assets/textures/skybox/left.jpg"
#define DEFAULT_SKYBOX2_RIGHT "Assets/textures/skybox/right.jpg"
#define DEFAULT_SKYBOX2_BACK "Assets/textures/skybox/back.jpg"
#define DEFAULT_SKYBOX2_FRONT "Assets/textures/skybox/front.jpg"

#define DEFAULT_SKYBOX_TOP "Assets/skyboxes/multi2/elyvisions/sh_up.png"
#define DEFAULT_SKYBOX_BOTTOM "Assets/skyboxes/multi2/elyvisions/sh_dn.png"
#define DEFAULT_SKYBOX_LEFT "Assets/skyboxes/multi2/elyvisions/sh_lf.png"
#define DEFAULT_SKYBOX_RIGHT "Assets/skyboxes/multi2/elyvisions/sh_rt.png"
#define DEFAULT_SKYBOX_BACK "Assets/skyboxes/multi2/elyvisions/sh_bk.png"
#define DEFAULT_SKYBOX_FRONT "Assets/skyboxes/multi2/elyvisions/sh_ft.png"

#define DEFAULT_SKYBOX_CLOUD_TEXTURE "Assets/textures/cloud.jpg"

#define UBO_SIZE() sizeof(float) * (16 + 16 + 16)

namespace YG
{
	namespace Core
	{
		struct OnKeyPress
		{
			virtual void operator()(sf::Keyboard::Key key)
			{
			}
		};

		class Renderer
		{
			public:
				bool fog_enabled;
				float fog_min_distance;
				float fog_max_distance;
				Math::Color fog_color;
				sf::Clock clock;
				float deltaTime;

				Renderer(unsigned int width = 800, unsigned int height = 600, const std::string& title = std::string("OpenGLRenderer"), bool fullscreen = false);
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

				Light* getLight(unsigned int index)
				{
					return m_lights[index % MAXIMUM_LIGHT];
				}

				void setPostProcessShader(std::string fs)
				{
					m_postProcessShader->setFragmentShaderPath(fs);
					m_postProcessShader->Load();
				}

				bool isPostProcessEnabled() const { return m_postProcessEnabled; }

				void enablePostProcess(bool state) { m_postProcessEnabled = state; }

				bool isSkyboxEnabled() const { return m_skyboxEnabled; }

				void enableSkybox(bool state) { m_skyboxEnabled = state; }

				void setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front)
				{
					std::vector<std::string> paths = { right, left, top, bottom, back, front };
					m_skyboxCubemap = new Texture(CUBEMAP, paths, 7);
					m_skyboxCubemap->Load();
				}

				void addKeypressEvent(OnKeyPress *evt)
				{
					m_keyPressEvents.push_back(evt);
				}

			protected:
				void createDisplay(const std::string& title = "OpenGLRenderer", bool fullscreen = false);

				GLuint bakeShadowMap(Scene *scene, Camera *camera, Light& L, Shader *shadowMapShader = new Shader("Assets/shaders/shadowMap.vs", "Assets/shaders/shadowMap.fs"));

				std::vector<OnKeyPress*> m_keyPressEvents;
				bool m_postProcessEnabled;
				bool m_skyboxEnabled;
				GLuint m_skyboxVAO;
				GLuint m_skyboxIBO;
				Shader *m_skyboxShader;
				Texture *m_cloudTexture;
				Texture *m_skyboxCubemap;
				GLuint m_postProcessVAO;
				GLuint m_postProcessIBO;
				RenderTarget *m_postProcessPass;
				Shader *m_postProcessShader;
				RenderTarget *m_shadowMap;
				glm::mat4 m_shadowMapWVP;
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