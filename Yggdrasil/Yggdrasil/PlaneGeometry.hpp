#ifndef YGGDRASIL_PLANE_GEOMETRY_HPP
#define YGGDRASIL_PLANE_GEOMETRY_HPP

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
		class PlaneGeometry : public Geometry
		{
			public:
				PlaneGeometry(float size)
					: Geometry()
				{
					m_vertice.push_back(Vertex(Math::Vector3(-size, -size, 0.0f), Math::Vector3(-size, -size, 0.0f), Math::Vector3(), Math::Vector2(0.0f, 0.0f)));
					m_vertice.push_back(Vertex(Math::Vector3(-size, size, 0.0f), Math::Vector3(-size, size, 0.0f), Math::Vector3(), Math::Vector2(0.0f, 1.0f)));
					m_vertice.push_back(Vertex(Math::Vector3(size, -size, 0.0f), Math::Vector3(size, -size, 0.0f), Math::Vector3(), Math::Vector2(1.0f, 0.0f)));

					m_vertice.push_back(Vertex(Math::Vector3(size, -size, 0.0f), Math::Vector3(size, -size, 0.0f), Math::Vector3(), Math::Vector2(1.0f, 0.0f)));
					m_vertice.push_back(Vertex(Math::Vector3(-size, size, 0.0f), Math::Vector3(-size, size, 0.0f), Math::Vector3(), Math::Vector2(0.0f, 1.0f)));
					m_vertice.push_back(Vertex(Math::Vector3(size, size, 0.0f), Math::Vector3(size, size, 0.0f), Math::Vector3(), Math::Vector2(1.0f, 1.0f)));

					m_indices.push_back(0);
					m_indices.push_back(1);
					m_indices.push_back(2);
					m_indices.push_back(3);
					m_indices.push_back(4);
					m_indices.push_back(5);

					Load();
				}

			protected:
		};
	};
};

#endif