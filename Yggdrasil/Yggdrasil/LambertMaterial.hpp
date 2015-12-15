#ifndef YGGDRASIL_LAMBERT_MATERIAL_HPP
#define YGGDRASIL_LAMBERT_MATERIAL_HPP

#include <iostream>
#include <string>
#include <strstream>
#include "Asset.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Color.hpp"
#include "Material.hpp"

#include "glew.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace YG
{
	namespace Core
	{
		class LambertMaterial : public Material
		{
			public:
				Math::Color diffuse;
				float diffuseIntensity;

				LambertMaterial(Math::Color ambient = Math::Color(1.0f, 1.0f, 1.0f), Math::Color diffuse = Math::Color(0.7f, 0.7f, 0.7f))
					: Material("Assets/shaders/lambert.vs", "Assets/shaders/lambert.fs")
				{
					this->ambient = ambient;
					this->diffuse = diffuse;
					this->diffuseIntensity = 1.0f;
					Load();
				}

				void BindProperties(GLuint shaderID)
				{
					GLuint ambientLocation = glGetUniformLocation(shaderID, "u_material.ambient");
					glUniform3f(ambientLocation, ambient.r, ambient.g, ambient.b);
					GLuint ambientIntensityLocation = glGetUniformLocation(shaderID, "u_material.ka");
					glUniform1f(ambientIntensityLocation, ambientIntensity);
					GLuint diffuseLocation = glGetUniformLocation(shaderID, "u_material.diffuse");
					glUniform3f(diffuseLocation, diffuse.r, diffuse.g, diffuse.b);
					GLuint diffuseIntensityLocation = glGetUniformLocation(shaderID, "u_material.kd");
					glUniform1f(diffuseIntensityLocation, diffuseIntensity);
				}

			protected:
		};
	};
};

#endif