#ifndef YGGDRASIL_TEXTURE_HPP
#define YGGDRASIL_TEXTURE_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"
#include "Image.hpp"
#include "Vector2.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		enum TEXTURE_TYPE
		{
			TEXTURE,
			CUBEMAP
		};

		class Texture : public Resource
		{
			public:
				Math::Vector2 repeat;

				Texture(TEXTURE_TYPE type = TEXTURE, std::vector<std::string> paths = std::vector<std::string>(), GLuint unit = 0)
					: Resource("TEXTURE")
				{
					m_paths = paths;
					m_unit = unit;
					m_type = type;
					repeat.x = repeat.y = 1.0f;
				}

				void Load()
				{
					m_loaded = false;

					if (m_paths.size())
					{
						std::vector<Image> images;
						for (std::string path : m_paths)
						{
							images.push_back(Image(path));
						}

						switch (m_type)
						{
							case TEXTURE:
								glGenTextures(1, &m_texture);
								glBindTexture(GL_TEXTURE_2D, m_texture);
								glTexImage2D(	GL_TEXTURE_2D, 
												0, 
												((images.at(0).getComp() == 3) ? GL_RGB : GL_RGBA),
												images.at(0).getWidth(), images.at(0).getHeight(),
												0,
												((images.at(0).getComp() == 3) ? GL_RGB : GL_RGBA),
												GL_UNSIGNED_BYTE,
												images.at(0).getData()
								);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
								glGenerateMipmap(GL_TEXTURE_2D);
								glBindTexture(GL_TEXTURE_2D, 0);
								break;

							case CUBEMAP:
								if (images.size() >= 6)
									glGenTextures(1, &m_texture);
									glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
									for (unsigned int i = 0; i < 6; ++i)
									{
										glTexImage2D(
											GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
											0,
											GL_RGB,
											images.at(i).getWidth(), images.at(i).getHeight(),
											0,
											GL_RGB,
											GL_UNSIGNED_BYTE,
											images.at(i).getData()
										);
									}
									glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
									glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
									glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
									glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
									glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
									glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
								break;

							default:
								break;
						}

						m_loaded = true;
					}
				}

				void Bind()
				{
					if (m_loaded)
					{
						glActiveTexture(GL_TEXTURE0 + m_unit);
						glBindTexture(GL_TEXTURE_2D, m_texture);
					}
				}

				void Unbind()
				{
					if (m_loaded)
					{
						//glBindTexture(GL_TEXTURE_2D, 0);
					}
				}

				std::vector<std::string> getPaths() const { return m_paths; }
				void setPaths(std::vector<std::string> paths) { m_paths = paths; }

				TEXTURE_TYPE getTextureType() const { return m_type; }

				GLuint getUnit() const { return m_unit; }

				GLuint getTextureId() const { return m_texture; }

				bool isLoaded() const { return m_loaded; }

			protected:
				std::vector<std::string> m_paths;
				TEXTURE_TYPE m_type;
				GLuint m_unit;
				GLuint m_texture;
				bool m_loaded;
		};
	};
};

#endif