#ifndef YGGDRASIL_MATERIAL_HPP
#define YGGDRASIL_MATERIAL_HPP

#include <iostream>
#include <string>
#include <strstream>
#include "Asset.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#define MAXIMUM_TEXTURE 16

#define DEFAULT_VERTEX_SHADER "#version 330\n" \
								"layout(location=0) in vec3 a_position;\n" \
								"layout(location=1) in vec3 a_normal;\n" \
								"layout(location=2) in vec2 a_uv;\n" \
								"uniform mat4 u_view;\n" \
								"uniform mat4 u_proj;\n" \
								"uniform mat4 u_world;\n" \
								"out vec3 v_position;\n" \
								"out vec3 v_normal;\n" \
								"out vec2 v_uv;\n" \
								"void main(void){\n" \
								"gl_Position = u_proj * u_view * u_world * vec4(a_position, 1.0);\n" \
								"v_position = a_position;\n" \
								"v_normal = a_normal;\n" \
								"v_uv = a_uv;\n" \
								"}"

#define DEFAULT_FRAGMENT_SHADER "#version 330\n" \
								"in vec3 v_position;\n" \
								"in vec3 v_normal;\n" \
								"in vec2 v_uv;\n" \
								"out vec4 o_color;\n" \
								"void main(void){\n" \
								"o_color = vec4(v_normal, 1.0);\n" \
								"}"

namespace YG
{
	namespace Core
	{
		class Material : public Asset
		{
			public:
				Material(const std::string& vs = std::string(), const std::string& fs = std::string())
					: Asset("Material")
				{
					if (!vs.empty() && !fs.empty())
					{
						m_resources.insert(std::pair<std::string, Resource*>("shader", new Shader()));
						static_cast<Shader*>(m_resources["shader"])->Load(vs, fs);
					}
					else
					{
						m_resources.insert(std::pair<std::string, Resource*>("shader", new Shader()));
						static_cast<Shader*>(m_resources["shader"])->Load(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
					}
					Load();
				}

				void Load()
				{
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						std::strstream stream;
						stream << "texture" << i;
						m_resources.insert(std::pair<std::string, Resource*>(stream.str(), new Texture(TEXTURE, std::vector<std::string>(), i)));
					}
					m_textureLoadingId = 0;
				}

				void loadTexture(const std::string& path)
				{
					std::strstream stream;
					stream << "texture" << m_textureLoadingId;
					static_cast<Texture*>(m_resources[stream.str()])->setPaths(std::vector<std::string>{ path });
					static_cast<Texture*>(m_resources[stream.str()])->Load();
					m_textureLoadingId = (m_textureLoadingId + 1) % MAXIMUM_TEXTURE;
				}

				void Bind()
				{
					static_cast<Shader*>(m_resources["shader"])->Bind();
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						std::strstream stream;
						stream << "texture" << i;
						static_cast<Texture*>(m_resources[stream.str()])->Bind();
					}
				}

				void Unbind()
				{
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						std::strstream stream;
						stream << "texture" << i;
						static_cast<Texture*>(m_resources[stream.str()])->Unbind();
					}
					static_cast<Shader*>(m_resources["shader"])->Unbind();
				}

			protected:
				unsigned int m_textureLoadingId;
		};
	};
};

#endif