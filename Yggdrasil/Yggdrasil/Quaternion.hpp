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

				Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
				{
					this->x = x;
					this->y = y;
					this->z = z;
					this->w = w;
				}

				Quaternion(const Quaternion& u)
				{
					this->x = u.x;
					this->y = u.y;
					this->z = u.z;
					this->w = u.w;
				}

				Quaternion(const Vector3& u)
				{
					x = u.x;
					y = u.y;
					z = u.z;
					w = 0.0f;
				}

				Quaternion operator+(const Quaternion& u)
				{
					Quaternion v = Quaternion(*this);
					v.x = v.x + u.x;
					v.y = v.y + u.y;
					v.z = v.z + u.z;
					v.w = v.w + u.w;
					return v;
				}

				Quaternion& operator+=(const Quaternion& u)
				{
					*this = operator+(u);
					return *this;
				}

				Quaternion operator-(const Quaternion& u)
				{
					Quaternion v = Quaternion(*this);
					v.x = v.x - u.x;
					v.y = v.y - u.y;
					v.z = v.z - u.z;
					v.w = v.w - u.w;
					return v;
				}

				Quaternion& operator-=(const Quaternion& u)
				{
					*this = operator-(u);
					return *this;
				}

				Quaternion operator*(const Quaternion& u)
				{
					Quaternion v = Quaternion(*this);
					v.x = v.x * u.w + v.y * u.z - v.z * u.y + v.w * u.x;
					v.y = -v.x * u.z + v.y * u.w + v.z * u.x + v.w * u.y;
					v.z = v.x * u.y - v.y * u.x + v.z * u.w + v.w * u.z;
					v.w = -v.x * u.x - v.y * u.y - v.z * u.z + v.w * u.w;
					return v;
				}

				Quaternion& operator*=(const Quaternion& u)
				{
					*this = operator*(u);
					return *this;
				}

				Quaternion operator-()
				{
					Quaternion v = Quaternion(*this);
					v.x = -v.x;
					v.y = -v.y;
					v.z = -v.z;
					return v;
				}

				Quaternion operator=(const Quaternion& u)
				{
					Quaternion v = Quaternion(u);
					return v;
				}

				bool operator==(const Quaternion& u)
				{
					return (x == u.x) && (y == u.y) && (z == u.z);
				}

				bool operator<(const Quaternion& u)
				{
					return ((x < u.x) && (y < u.y) && (z < u.z));
				}

				bool operator>(const Quaternion& u)
				{
					return (!operator==(u) && !operator<(u));
				}

				bool operator<=(const Quaternion& u)
				{
					return (operator==(u) || operator<(u));
				}

				bool operator>=(const Quaternion& u)
				{
					return (operator==(u) || operator>(u));
				}

				bool operator!=(const Quaternion& u)
				{
					return !operator==(u);
				}

				Quaternion conjugate()
				{
					return -(*this);
				}

				float length()
				{
					return sqrt(x * x + y * y + z * z + w * w);
				}

				float lengthSq()
				{
					return (x * x + y * y + z * z + w * w);
				}

				float distance(Vector3& u)
				{
					return u.length() - length();
				}

				float distanceSq(Vector3& u)
				{
					return u.lengthSq() - lengthSq();
				}

				Quaternion& normalize()
				{
					float l = length();
					x = x / l;
					y = y / l;
					z = z / l;
					w = w / l;
					return *this;
				}

				Quaternion normalized()
				{
					Quaternion q(*this);
					float l = length();
					q.x = q.x / l;
					q.y = q.y / l;
					q.z = q.z / l;
					q.w = q.w / l;
					return q;
				}

				void rotationQuaternion(float angle, const Vector3& u)
				{
					w = cos(angle / 2.0f);
					x = sin(angle / 2.0f) * u.x;
					y = sin(angle / 2.0f) * u.y;
					z = sin(angle / 2.0f) * u.z;
				}

				friend std::ostream& operator<<(std::ostream& out, const Quaternion& u);

			private:
		};
	};
};

#endif