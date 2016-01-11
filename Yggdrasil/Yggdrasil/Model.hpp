#ifndef YGGDRASIL_MODEL_HPP
#define YGGDRASIL_MODEL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "Material.hpp"
#include "PhongMaterial.hpp"
#include "Mesh.hpp"
#include "Resource.hpp"
#include "Transform.hpp"
#include "tiny_obj_loader.h"

namespace YG
{
	namespace Core
	{
		class Model : public Resource
		{
			public:
				Model(std::string path)
					: Resource("MODEL")
				{
					m_path = path;
					Load();
				}

				void Load()
				{
					m_loaded = false;

					Math::Vector2 quadUVS[] {
						Math::Vector2(0.0f, 0.0f),
						Math::Vector2(0.0f, 1.0f),
						Math::Vector2(1.0f, 0.0f),
						Math::Vector2(1.0f, 1.0f)
					};
					unsigned int quadUVIndex = 0;

					m_geometries.clear();
					std::vector<tinyobj::shape_t> shapes;
					std::vector<tinyobj::material_t> materials;
					std::string err = tinyobj::LoadObj(shapes, materials, m_path.c_str());
					for (unsigned int shapeID = 0; shapeID < shapes.size(); ++shapeID)
					{
						const std::vector<unsigned int> &indices = shapes[shapeID].mesh.indices;
						const std::vector<float> &positions = shapes[shapeID].mesh.positions;
						const std::vector<float> &normals = shapes[shapeID].mesh.normals;
						const std::vector<float> &texcoords = shapes[shapeID].mesh.texcoords;

						std::vector<Vertex> vertice;
						std::vector<GLuint> indexes;
						quadUVIndex = 0;

						unsigned int j = 0;
						for (unsigned int i = 0; i < positions.size(); i += 3)
						{
							vertice.push_back(Vertex(
								Math::Vector3(positions.at(i), positions.at(i + 1), positions.at(i + 2)),
								normals.size() ? Math::Vector3(normals.at(i), normals.at(i + 1), normals.at(i + 2)) : Math::Vector3(0.0f, 0.0f, 0.0f),
								Math::Vector3(0.0f, 0.0f, 0.0f),
								texcoords.size() ? Math::Vector2(texcoords.at(j), texcoords.at(j + 1)) : quadUVS[quadUVIndex]
							));
							j += 2;
							quadUVIndex = (quadUVIndex + 1) % 4;
						}

						for (int j = 0; j < (int)indices.size(); ++j){ indexes.push_back(indices.at(j)); }
						Geometry *geo = new Geometry(vertice, indexes);
						m_geometries.push_back(geo);
					}
					m_loaded = true;
				}

				Mesh* Instanciate(unsigned int meshIndex)
				{
					if (meshIndex >= m_geometries.size()) { return 0; }
					Geometry *geometry = m_geometries.at(meshIndex);
					Material *material = new PhongMaterial(Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), Math::Color(1.0f, 1.0f, 1.0f), 50.0f);
					return new Mesh(geometry, material);
				}

				bool isLoaded() const { return m_loaded; }

				std::string getPath() const { return m_path; }
				void setPath(const std::string& path) { m_path = path; }

			protected:
				bool m_loaded;
				std::string m_path;
				std::vector<Geometry*> m_geometries;
		};
	};
};

#endif