#ifndef YGGDRASIL_SHADER_HPP
#define YGGDRASIL_SHADER_HPP

#include <iostream>
#include <fstream>
#include "Resource.hpp"
#include "File.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class Shader : public Resource
		{
			public:
				Shader(std::string vs = std::string(), std::string fs = std::string(), std::string gs = std::string())
					: Resource("SHADER")
				{
					m_loaded = false;
					m_vsPath = vs;
					m_fsPath = fs;
					m_gsPath = gs;
					Load();
				}

				void Load()
				{
					m_loaded = false;

					if (!m_vsPath.empty())
					{
						m_vs = glCreateShader(GL_VERTEX_SHADER);
						const char* content = File::CLoad(m_vsPath.c_str());
						glShaderSource(m_vs, 1, (const char**)&content, 0);
						glCompileShader(m_vs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_vs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_vs, 512, 0, infoLog);
							std::cerr << "Vertex Shader compilation failed : " << infoLog << std::endl;
						}
					}

					if (!m_fsPath.empty())
					{
						m_fs = glCreateShader(GL_FRAGMENT_SHADER);
						const char* content = File::CLoad(m_fsPath.c_str());
						glShaderSource(m_fs, 1, (const char**)&content, 0);
						glCompileShader(m_fs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_fs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_fs, 512, 0, infoLog);
							std::cerr << "Fragment Shader compilation failed : " << infoLog << std::endl;
						}
					}

					if (!m_gsPath.empty())
					{
						m_gs = glCreateShader(GL_GEOMETRY_SHADER);
						const char* content = File::CLoad(m_gsPath.c_str());
						glShaderSource(m_gs, 1, (const char**)&content, 0);
						glCompileShader(m_gs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_gs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_gs, 512, 0, infoLog);
							std::cerr << "Geometry Shader compilation failed : " << infoLog << std::endl;
						}
					}

					m_id = glCreateProgram();
					if (!m_vsPath.empty()) { glAttachShader(m_id, m_vs); }
					if (!m_fsPath.empty()) { glAttachShader(m_id, m_fs); }
					if (!m_gsPath.empty()) { glAttachShader(m_id, m_gs); }
					glLinkProgram(m_id);
					int success;
					char infoLog[512];
					glGetProgramiv(m_id, GL_LINK_STATUS, &success);
					if (!success)
					{
						glGetProgramInfoLog(m_id, 512, 0, infoLog);
						std::cerr << "Shader program link failed : " << infoLog << std::endl;
					}
					else
					{
						m_loaded = true;
					}
				}

				void Load(const std::string &vertexShaderContent, const std::string &fragmentShaderContent, const std::string &geometryShaderContent = "")
				{
					m_loaded = false;

					if (vertexShaderContent.size())
					{
						m_vs = glCreateShader(GL_VERTEX_SHADER);
						const char* content = vertexShaderContent.c_str();
						glShaderSource(m_vs, 1, &content, 0);
						glCompileShader(m_vs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_vs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_vs, 512, 0, infoLog);
							std::cerr << "Vertex Shader compilation failed : " << infoLog << std::endl;
						}
					}

					if (fragmentShaderContent.size())
					{
						m_fs = glCreateShader(GL_FRAGMENT_SHADER);
						const char* content = fragmentShaderContent.c_str();
						glShaderSource(m_fs, 1, &content, 0);
						glCompileShader(m_fs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_fs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_fs, 512, 0, infoLog);
							std::cerr << "Fragment Shader compilation failed : " << infoLog << std::endl;
						}
					}

					if (geometryShaderContent.size())
					{
						m_gs = glCreateShader(GL_GEOMETRY_SHADER);
						const char* content = geometryShaderContent.c_str();
						glShaderSource(m_gs, 1, &content, 0);
						glCompileShader(m_gs);
						int success;
						char infoLog[512];
						glGetShaderiv(m_gs, GL_COMPILE_STATUS, &success);
						if (!success)
						{
							glGetShaderInfoLog(m_gs, 512, 0, infoLog);
							std::cerr << "Geometry Shader compilation failed : " << infoLog << std::endl;
						}
					}

					m_id = glCreateProgram();
					if (vertexShaderContent.size()) {
						glAttachShader(m_id, m_vs); 
					}
					if (fragmentShaderContent.size()) {
						glAttachShader(m_id, m_fs); 
					}
					if (geometryShaderContent.size()) {
						glAttachShader(m_id, m_gs); 
					}
					glLinkProgram(m_id);
					int success;
					char infoLog[512];
					glGetProgramiv(m_id, GL_LINK_STATUS, &success);
					if (!success)
					{
						glGetProgramInfoLog(m_id, 512, 0, infoLog);
						std::cerr << "Shader program link failed : " << infoLog << std::endl;
					}
					else
					{
						m_loaded = true;
					}
				}

				void Bind()
				{
					if (m_loaded)
					{
						glUseProgram(m_id);
					}
				}

				void Unbind()
				{
					if (m_loaded)
					{
						glUseProgram(0);
					}
				}

				std::string getVertexShaderPath() const { return m_vsPath; }
				std::string getFragmentShaderPath() const { return m_fsPath; }
				std::string getGeometryShaderPath() const { return m_gsPath; }

				GLuint getId() { return m_id; }

			protected:
				bool m_loaded;
				GLuint m_id;
				std::string m_vsPath;
				std::string m_fsPath;
				std::string m_gsPath;
				GLuint m_vs;
				GLuint m_fs;
				GLuint m_gs;
		};
	};
};

#endif