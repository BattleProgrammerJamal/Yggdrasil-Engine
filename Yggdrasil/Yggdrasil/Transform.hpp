#ifndef YGGDRASIL_TRANSFORM_HPP
#define YGGDRASIL_TRANSFORM_HPP

#include <iostream>
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"

namespace YG
{
	class Transform
	{
		public:
			Vector3 position;
			Vector3 rotation;
			Vector3 scale;
			Matrix4 world;

			Transform()
			{
				scale.x = scale.y = scale.z = 1.0f;
			}

			void Translate(const Vector3& u)
			{
				position = position + u;
				updateWorldMatrix();
			}

			void Rotate(const Vector3& u)
			{
				rotation = rotation + u;
				updateWorldMatrix();
			}

			void Scale(const Vector3& u)
			{
				scale = scale + u;
				updateWorldMatrix();
			}

			void updateWorldMatrix()
			{
				Matrix4 T = Matrix4::TranslationMatrix(position);
				Matrix4 R = Matrix4::RotationMatrix(rotation);
				Matrix4 S = Matrix4::ScaleMatrix(scale);
				world = S * R * T;
			}
	};
};

#endif