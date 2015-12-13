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
				GLenum renderStyle;

				Mesh()
					: Actor("Mesh")
				{
					m_geometry = 0;
					m_material = 0;
					renderStyle = GL_TRIANGLE_STRIP;
				}

				Mesh(Geometry *geometry, Material *material)
					: Actor("Mesh")
				{
					m_geometry = geometry;
					m_material = material;
					renderStyle = GL_TRIANGLE_STRIP;
				}

				~Mesh()
				{
					delete m_geometry;
					delete m_material;
				}

				Geometry* getGeometry() const { return m_geometry; }
				void setGeometry(Geometry *geometry) { m_geometry = geometry; }

				Material* getMaterial() const { return m_material; }
				void setMaterial(Material *material) { m_material = material; }

			protected:
				Geometry* m_geometry;
				Material* m_material;
		};
	};
};

#endif