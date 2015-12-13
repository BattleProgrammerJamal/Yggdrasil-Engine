#ifndef YGGDRASIL_GEOMETRY_HPP
#define YGGDRASIL_GEOMETRY_HPP

#include <iostream>
#include "Asset.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#define BUFFER_OFFSET(idx) (void*)(sizeof(float) * idx)

namespace YG
{
	namespace Core
	{
		struct Vertex
		{
			static const GLsizei stride = static_cast<GLsizei>(sizeof(float) * 11);

			Math::Vector3 position;
			Math::Vector3 normal;
			Math::Vector3 tangent;
			Math::Vector2 uv;

			Vertex(Math::Vector3 position, Math::Vector3 normal, Math::Vector3 tangent, Math::Vector2 uv)
			{
				this->position = position;
				this->normal = normal;
				this->tangent = tangent;
				this->uv = uv;
			}
		};

		class Geometry : public Asset
		{
			public:
				Geometry()
					: Asset("GEOMETRY")
				{
					m_vao = m_vbo = m_ibo = 0;
				}

				Geometry(std::vector<Vertex> vertice, std::vector<GLuint> indices)
					: Asset("GEOMETRY")
				{
					m_vertice = vertice;
					m_indices = indices;
					m_vao = m_vbo = m_ibo = 0;
					Load();
				}

				virtual void Load()
				{
					std::vector<float> vertice;
					for (Vertex vert : m_vertice)
					{
						vertice.push_back(vert.position.x);
						vertice.push_back(vert.position.y);
						vertice.push_back(vert.position.z);
						vertice.push_back(vert.normal.x);
						vertice.push_back(vert.normal.y);
						vertice.push_back(vert.normal.z);
						vertice.push_back(vert.tangent.x);
						vertice.push_back(vert.tangent.y);
						vertice.push_back(vert.tangent.z);
						vertice.push_back(vert.uv.x);
						vertice.push_back(vert.uv.y);
					}

					glGenVertexArrays(1, &m_vao);
					glBindVertexArray(m_vao);
					glGenBuffers(1, &m_vbo);
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertice.size(), (const void*)&vertice[0], GL_STATIC_DRAW);
					
					glEnableVertexAttribArray(0);
					glEnableVertexAttribArray(1);
					glEnableVertexAttribArray(2);
					glEnableVertexAttribArray(3);
					
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(0));
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(3));
					glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(6));
					glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, Vertex::stride, BUFFER_OFFSET(9));
					
					glBindVertexArray(0);

					glGenBuffers(1, &m_ibo);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_indices.size(), (const void*)&m_indices[0], GL_STATIC_DRAW);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				}

				GLuint getVAO() const { return m_vao; }
				GLuint getVBO() const { return m_vbo; }
				GLuint getIBO() const { return m_ibo; }

				std::vector<Vertex> getVertice() const { return m_vertice; }
				void setVertice(std::vector<Vertex> vertice) { m_vertice = vertice; }

				std::vector<GLuint> getIndices() const { return m_indices; }
				void setIndices(std::vector<GLuint> indices) { m_indices = indices; }

			protected:
				GLuint m_vao;
				GLuint m_vbo;
				GLuint m_ibo;
				std::vector<Vertex> m_vertice;
				std::vector<GLuint> m_indices;
		};
	};
};

#endif