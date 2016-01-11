#ifndef YGGDRASIL_BOX_GEOMETRY_HPP
#define YGGDRASIL_BOX_GEOMETRY_HPP

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
		class BoxGeometry : public Geometry
		{
			public:
				BoxGeometry(float width, float height, float depth)
					: Geometry()
				{
					m_vertice = {
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000059f, 1.0f - 0.000004f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000103f, 1.0f - 0.336048f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(1.000023f, 1.0f - 0.000013f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.999958f, 1.0f - 0.336064f)),
						Vertex(Math::Vector3(1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336024f, 1.0f - 0.671877f)),
						Vertex(Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667969f, 1.0f - 0.671889f)),
						Vertex(Math::Vector3(1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(1.000023f, 1.0f - 0.000013f)),
						Vertex(Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.668104f, 1.0f - 0.000013f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000059f, 1.0f - 0.000004f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336098f, 1.0f - 0.000071f)),
						Vertex(Math::Vector3(1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336024f, 1.0f - 0.671877f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(1.000004f, 1.0f - 0.671847f)),
						Vertex(Math::Vector3(-1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.999958f, 1.0f - 0.336064f)),
						Vertex(Math::Vector3(1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.668104f, 1.0f - 0.000013f)),
						Vertex(Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f)),
						Vertex(Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.668104f, 1.0f - 0.000013f)),
						Vertex(Math::Vector3(1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336098f, 1.0f - 0.000071f)),
						Vertex(Math::Vector3(1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000103f, 1.0f - 0.336048f)),
						Vertex(Math::Vector3(1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000004f, 1.0f - 0.671870f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336024f, 1.0f - 0.671877f)),
						Vertex(Math::Vector3(1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.000103f, 1.0f - 0.336048f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.336024f, 1.0f - 0.671877f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.335973f, 1.0f - 0.335903f)),
						Vertex(Math::Vector3(1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667969f, 1.0f - 0.671889f)),
						Vertex(Math::Vector3(-1.0f, 1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(1.000004f, 1.0f - 0.671847f)),
						Vertex(Math::Vector3(1.0f, -1.0f, 1.0f), Math::Vector3(), Math::Vector3(), Math::Vector2(0.667979f, 1.0f - 0.335851f))
					};
						

					for (unsigned int i = 0; i < m_vertice.size(); ++i)
					{ 
						m_vertice.at(i).position.x *= width;
						m_vertice.at(i).position.y *= height;
						m_vertice.at(i).position.z *= depth;
						m_indices.push_back(i); 
					}

					Load();
				}

			protected:
		};
	};
};

#endif