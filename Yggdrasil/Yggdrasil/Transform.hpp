#ifndef YGGDRASIL_TRANSFORM_HPP
#define YGGDRASIL_TRANSFORM_HPP

#include <iostream>
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"

#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/type_ptr.hpp"

namespace YG
{
	namespace Math
	{
		class Transform
		{
			public:
				Vector3 position;
				Vector3 rotation;
				Vector3 scale;
				glm::mat4 world;

				Transform()
				{
					scale.x = scale.y = scale.z = 1.0f;
				}

				void Translate(const Vector3& u)
				{
					position = position + u;
				}

				void Rotate(const Vector3& u)
				{
					rotation = rotation + u;
				}

				void Scale(const Vector3& u)
				{
					scale = scale * u;
				}

				void updateWorldMatrix()
				{
					glm::mat4 T = glm::translate(glm::vec3(position.x, position.y, position.z));
					glm::mat4 R = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
					glm::mat4 S = glm::scale(glm::vec3(scale.x, scale.y, scale.z));

					Math::Quaternion q =	Math::Quaternion(Math::Vector3(0.0f, 0.0f, 1.0f), rotation.z) *
											Math::Quaternion(Math::Vector3(0.0f, 1.0f, 0.0f), rotation.y) *
											Math::Quaternion(Math::Vector3(1.0f, 0.0f, 0.0f), rotation.x);
					q.normalize();
					q.setRotationMatrix(glm::value_ptr(R));

					world = S * R * T;
				}
		};
	};
};

#endif