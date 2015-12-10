#ifndef YGGDRASIL_RENDERER_HPP
#define YGGDRASIL_RENDERER_HPP

#include <iostream>
#include <string>
#include "Scene.hpp"
#include "Camera.hpp"
#include "Color.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 3

namespace YG
{
	namespace Core
	{
		class Renderer
		{
			public:
				Renderer(unsigned int width = 800, unsigned int height = 600, const std::string& title = std::string("OpenGLRenderer"));
				virtual ~Renderer();

				bool render(const Scene *scene, const Camera *camera);

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

			protected:
				void createDisplay(const std::string& title = "OpenGLRenderer");

				sf::Window* m_window;
				sf::Event m_event;
				unsigned int m_width;
				unsigned int m_height;
				bool m_fullscreen;
				Math::Color m_clearColor;
		};
	};
};

#endif