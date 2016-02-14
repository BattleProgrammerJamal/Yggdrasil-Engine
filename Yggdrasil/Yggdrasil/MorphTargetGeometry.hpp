#ifndef YGGDRASIL_MORPH_TARGET_GEOMETRY_HPP
#define YGGDRASIL_MORPH_TARGET_GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Vector3.hpp"
#include "Geometry.hpp"

#define MORPH_TARGET_MAXIMUM 2

namespace YG
{
	namespace Core
	{
		class MorphTargetGeometry : public Geometry
		{
			public:
				MorphTargetGeometry()
					: Geometry()
				{
				}

				MorphTargetGeometry(std::vector<Vertex> vertice, std::vector<GLuint> indices)
					: Geometry(vertice, indices)
				{
				}

				Geometry* getMorphTarget(unsigned int index)
				{

				}

				void setMorphTarget(unsigned int index, Geometry *morphTarget)
				{

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

				void LoadFlat(std::vector<float> vertice, std::vector<GLuint> indices)
				{
				}

				std::array<Geometry*, MORPH_TARGET_MAXIMUM> getMorphTargets() const { return m_morphTargets; }

			protected:
				std::array<Geometry*, MORPH_TARGET_MAXIMUM> m_morphTargets;
		};
	};
};

#endif