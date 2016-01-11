#ifndef YGGDRASIL_TERRAIN_GEOMETRY_HPP
#define YGGDRASIL_TERRAIN_GEOMETRY_HPP

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
		class TerrainGeometry : public Geometry
		{
			public:
				TerrainGeometry(float width, float height, unsigned int l, unsigned int c)
					: Geometry()
				{
					Math::Vector2 quadUV[] {
						Math::Vector2(0.0f, 0.0f),
						Math::Vector2(0.0f, 0.1f),
						Math::Vector2(1.0f, 1.0f),
						Math::Vector2(1.0f, 0.0f)
					};
					unsigned int quadUVIndex = 0;

					for (unsigned int i = 0; i < l; ++i)
					{
						unsigned int U = (i * (int)width) / l;
						for (unsigned int j = 0; j < c; ++j)
						{
							unsigned int V = (j * (int)height) / c;

							m_vertice.push_back(Vertex(
								Math::Vector3(U, 0.0f, V), Math::Vector3((float)i, 0.0f, (float)j),
								Math::Vector3(), Math::Vector2(quadUV[quadUVIndex].x, quadUV[quadUVIndex].y)));

							quadUVIndex = (quadUVIndex + 1) % 4;
						}
					}

					for (unsigned int i = 0; i < m_vertice.size(); ++i)
					{
						m_indices.push_back(i);
						m_indices.push_back((i + l + 1) % l);
						m_indices.push_back((i + l + 2) % l);
					}

					/*
					for (unsigned int i = 0; i < l * c + l; ++i)
					{
						m_indices.push_back(i);
						m_indices.push_back(i + l + 1);
						m_indices.push_back(i + l);

						m_indices.push_back(i + l + 1);
						m_indices.push_back(i);
						m_indices.push_back(i + 1);
					}
					*/
					Load();
				}

			protected:
		};
	};
};

#endif