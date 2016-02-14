#ifndef YGGDRASIL_QUATERNION_HPP
#define YGGDRASIL_QUATERNION_HPP

#include <iostream>
#include <cmath>
#include "Vector3.hpp"

namespace YG
{
	namespace Math
	{
		class Quaternion
		{
			public:
				float x, y, z, w;

				Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
				Quaternion(const Vector3& axis, float angle);
				Quaternion(const Quaternion& q);
				virtual ~Quaternion();

				Quaternion& operator=(const Quaternion& q);

				float length() const;
				float distance(const Quaternion& q) const;

				Quaternion& normalize();
				Quaternion normalized() const;

				Quaternion& conjugate();

				friend std::ostream& operator<<(std::ostream& out, const Quaternion& q);

				Quaternion operator+(const Quaternion& q);
				Quaternion& operator+=(const Quaternion& q);

				Quaternion operator-(const Quaternion& q);
				Quaternion& operator-=(const Quaternion& q);

				Quaternion operator*(const Quaternion& v);
				Quaternion& operator*=(const Quaternion& v);

				Quaternion operator*(const Vector3& q);
				Quaternion& operator*=(const Vector3& q);

				Quaternion operator-();

				bool operator==(const Quaternion& q);
				bool operator<(const Quaternion& q);
				bool operator!=(const Quaternion& q);
				bool operator>(const Quaternion& q);
				bool operator<=(const Quaternion& q);
				bool operator>=(const Quaternion& q);

				Quaternion& fromAxisAngle(const Vector3& axis, float angle);

				void setRotationMatrix(float *R);
		};
	};
};

#endif