#ifndef YGGDRASIL_MESH_HPP
#define YGGDRASIL_MESH_HPP

#include <iostream>
#include <vector>
#include "Actor.hpp"
#include "Material.hpp"
#include "Geometry.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class Mesh : public Actor
		{
			public:
				Mesh()
					: Actor("Mesh")
				{
				}
				virtual ~Mesh()
				{
				}

			protected:
				Geometry* m_geometry;
				Material* m_material;
		};
	};
};

#endif