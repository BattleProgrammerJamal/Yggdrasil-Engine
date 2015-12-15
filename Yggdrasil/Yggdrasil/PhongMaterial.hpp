#ifndef YGGDRASIL_PHONG_MATERIAL_HPP
#define YGGDRASIL_PHONG_MATERIAL_HPP

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
		class PhongMaterial : public Material
		{
			public:
				Math::Color diffuse;
				Math::Color specular;
				float shininess;
				float diffuseIntensity;
				float specularIntensity;

				PhongMaterial(Math::Color ambient = Math::Color(1.0f, 1.0f, 1.0f), Math::Color diffuse = Math::Color(0.7f, 0.7f, 0.7f), Math::Color specular = Math::Color(1.0f, 1.0f, 1.0f), float shininess = 50.0f)
					: Material("Assets/shaders/phong.vs", "Assets/shaders/phong.fs")
				{
					this->ambient = ambient;
					this->diffuse = diffuse;
					this->specular = specular;
					this->shininess = shininess;
					this->diffuseIntensity = 1.0f;
					this->specularIntensity = 1.0f;
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
					GLuint specularLocation = glGetUniformLocation(shaderID, "u_material.specular");
					glUniform3f(specularLocation, specular.r, specular.g, specular.b);
					GLuint specularIntensityLocation = glGetUniformLocation(shaderID, "u_material.ks");
					glUniform1f(specularIntensityLocation, specularIntensity);
					GLuint shininessLocation = glGetUniformLocation(shaderID, "u_material.shininess");
					glUniform1f(shininessLocation, shininess);
				}

			protected:
		};
	};
};

#endif