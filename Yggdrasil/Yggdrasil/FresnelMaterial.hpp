#ifndef YGGDRASIL_FRESNEL_MATERIAL_HPP
#define YGGDRASIL_FRESNEL_MATERIAL_HPP

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
		class FresnelMaterial : public Material
		{
			public:
				enum FRESNEL_OP_MODE
				{
					ADDITION = 0,
					SUBSTRACTION,
					MULTIPLICATION
				};

				Math::Color color;
				float roughness;
				FRESNEL_OP_MODE operationMode;

				FresnelMaterial(Math::Color color = Math::Color(1.0f, 1.0f, 1.0f), float roughness = 1.0f, FRESNEL_OP_MODE opMode = ADDITION)
					: Material("Assets/shaders/fresnel.vs", "Assets/shaders/fresnel.fs")
				{
					this->color = color;
					this->roughness = roughness;
					this->operationMode = opMode;
					Load();
				}

				void BindProperties(GLuint shaderID)
				{
					GLuint colorLocation = glGetUniformLocation(shaderID, "u_material.color");
					glUniform3f(colorLocation, color.r, color.g, color.b);
					GLuint roughnessLocation = glGetUniformLocation(shaderID, "u_material.roughness");
					glUniform1f(roughnessLocation, roughness);
					GLuint opModeLocation = glGetUniformLocation(shaderID, "u_material.operation");
					glUniform1i(opModeLocation, ((operationMode == ADDITION) ? 0 : (operationMode == SUBSTRACTION) ? 1 : 2));
				}

			protected:
		};
	};
};

#endif