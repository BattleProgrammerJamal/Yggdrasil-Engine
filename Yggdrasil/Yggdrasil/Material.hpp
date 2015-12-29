#ifndef YGGDRASIL_MATERIAL_HPP
#define YGGDRASIL_MATERIAL_HPP

#include <iostream>
#include <string>
#include <strstream>
#include "Asset.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Color.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

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
				Math::Color ambient;
				float ambientIntensity;

				Material(Math::Color ambient = Math::Color(1.0f, 1.0f, 1.0f))
					: Asset("Material")
				{
					m_resources.insert(std::pair<std::string, Resource*>("shader", new Shader("Assets/shaders/default.vs", "Assets/shaders/default.fs")));
					this->ambient = ambient;
					this->ambientIntensity = 0.6f;
					Load();
				}

				Material(const std::string& vs, const std::string& fs)
					: Asset("Material")
				{
					m_resources.insert(std::pair<std::string, Resource*>("shader", new Shader(vs, fs)));
					ambient.set(1.0f, 1.0f, 1.0f);
					this->ambientIntensity = 0.6f;
					Load();
				}

				~Material()
				{
					/*
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						if (m_textures[i])
						{
							delete m_textures[i];
						}
					}
					*/
				}

				void Load()
				{
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						m_textures[i] = new Texture(TEXTURE, std::vector<std::string>(), i);
					}
					m_textureLoadingId = 0;
				}

				Texture& loadTexture(const std::string& path)
				{
					m_textures[m_textureLoadingId]->setPaths(std::vector<std::string>{ path });
					m_textures[m_textureLoadingId]->Load();
					m_textureLoadingId = (m_textureLoadingId + 1) % MAXIMUM_TEXTURE;
					return *m_textures[(m_textureLoadingId - 1) % MAXIMUM_TEXTURE];
				}

				void Bind()
				{
					static_cast<Shader*>(m_resources["shader"])->Bind();
					GLuint shaderID = static_cast<Shader*>(m_resources["shader"])->getId();
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						m_textures[i]->Bind();
						std::strstream texName;
						texName << "u_texture" << i;
						GLuint texLoc = glGetUniformLocation(shaderID, texName.str());
						GLuint unit = m_textures[i]->getUnit();
						glUniform1i(texLoc, unit);
						std::strstream texRepeat;
						texRepeat << "u_texture_repeat" << i;
						GLuint texRepeatLoc = glGetUniformLocation(shaderID, texRepeat.str());
						glUniform2f(texRepeatLoc, m_textures[i]->repeat.x, m_textures[i]->repeat.y);
					}

					BindProperties(shaderID);
				}

				virtual void BindProperties(GLuint shaderID)
				{
					GLuint ambientLocation = glGetUniformLocation(shaderID, "u_material.ambient");
					glUniform3f(ambientLocation, ambient.r, ambient.g, ambient.b);
					GLuint ambientIntensityLocation = glGetUniformLocation(shaderID, "u_material.ka");
					glUniform1f(ambientIntensityLocation, ambientIntensity);
				}

				void Unbind()
				{
					for (unsigned int i = 0; i < MAXIMUM_TEXTURE; ++i)
					{
						m_textures[i]->Unbind();
					}
					static_cast<Shader*>(m_resources["shader"])->Unbind();
				}

				GLuint getShader() { return static_cast<Shader*>(m_resources["shader"])->getId(); }

				Resource* operator[](const std::string& name)
				{
					return m_resources[name];
				}

			protected:
				Texture* m_textures[MAXIMUM_TEXTURE];
				unsigned int m_textureLoadingId;
		};
	};
};

#endif