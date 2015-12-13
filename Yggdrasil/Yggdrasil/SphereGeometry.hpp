#ifndef YGGDRASIL_SPHERE_GEOMETRY_HPP
#define YGGDRASIL_SPHERE_GEOMETRY_HPP

#include <iostream>
#include "Asset.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Geometry.hpp"
#include "Math.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class SphereGeometry : public Geometry
		{
			public:
				SphereGeometry(float radius, GLuint stacks, GLuint slices)
					: Geometry()
				{
					for (unsigned int i = 0; i <= stacks; ++i)
					{
						float V = i / (float)stacks;
						float phi = V * PI;

						for (unsigned int j = 0; j <= slices; ++j)
						{
							float U = j / (float)slices;
							float theta = U * (PI * 2.0f);

							float X = cos(theta) * sin(phi);
							float Y = cos(phi);
							float Z = sin(theta) * sin(phi);

							Vertex vert(Math::Vector3(X, Y, Z) * Math::Vector3(radius, radius, radius), Math::Vector3(X, Y, Z), Math::Vector3(), Math::Vector2(U, V));

							m_vertice.push_back(vert);
						}
					}

					for (unsigned int i = 0; i < slices * stacks + slices; ++i)
					{
						m_indices.push_back(i);
						m_indices.push_back(i + slices + 1);
						m_indices.push_back(i + slices);

						m_indices.push_back(i + slices + 1);
						m_indices.push_back(i);
						m_indices.push_back(i + 1);
					}

					Load();
				}

			protected:
		};
	};
};

#endif