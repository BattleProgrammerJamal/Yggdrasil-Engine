#ifndef YGGDRASIL_VECTOR3_HPP
#define YGGDRASIL_VECTOR3_HPP

#include <iostream>
#include <cmath>

namespace YG
{
	namespace Math
	{
		class Vector3
		{
			public:
				float x, y, z;

				Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
				{
					this->x = x;
					this->y = y;
					this->z = z;
				}

				Vector3(const Vector3& u)
				{
					this->x = u.x;
					this->y = u.y;
					this->z = u.z;
				}

				float length() 
				{ 
					return sqrt(x * x + y * y + z * z);
				}

				float lengthSq()
				{
					return (x * x + y * y + z * z);
				}

				float distance(Vector3& u)
				{
					return u.length() - length();
				}

				float distanceSq(Vector3& u)
				{
					return u.lengthSq() - lengthSq();
				}

				Vector3& normalize()
				{
					float l = length();
					x = x / l;
					y = y / l;
					z = z / l;
					return *this;
				}

				Vector3 normalized()
				{
					float l = length();
					return Vector3(
						x / l,
						y / l,
						z / l
					);
				}

				float dot(const Vector3& u)
				{
					return (x * u.x) + (y * u.y) + (z * u.z);
				}

				Vector3 cross(const Vector3& u)
				{
					return Vector3(
						(y * u.z) - (z * u.y),
						(z * u.x) - (x * u.z),
						(x * u.y) - (y * u.x)
					);
				}

				Vector3 operator+(const Vector3& u)
				{
					Vector3 v = Vector3(*this);
					v.x = v.x + u.x;
					v.y = v.y + u.y;
					v.z = v.z + u.z;
					return v;
				}

				Vector3& operator+=(const Vector3& u)
				{
					*this = operator+(u);
					return *this;
				}

				Vector3 operator-(const Vector3& u)
				{
					Vector3 v = Vector3(*this);
					v.x = v.x - u.x;
					v.y = v.y - u.y;
					v.z = v.z - u.z;
					return v;
				}

				Vector3& operator-=(const Vector3& u)
				{
					*this = operator-(u);
					return *this;
				}

				Vector3 operator*(const Vector3& u)
				{
					Vector3 v = Vector3(*this);
					v.x = v.x * u.x;
					v.y = v.y * u.y;
					v.z = v.z * u.z;
					return v;
				}

				Vector3& operator*=(const Vector3& u)
				{
					*this = operator*(u);
					return *this;
				}

				Vector3 operator/(const Vector3& u)
				{
					Vector3 v = Vector3(*this);
					v.x = v.x / (u.x == 0.0f ? 1.0f : u.x);
					v.y = v.y / (u.y == 0.0f ? 1.0f : u.y);
					v.z = v.z / (u.z == 0.0f ? 1.0f : u.z);
					return v;
				}

				Vector3& operator/=(const Vector3& u)
				{
					*this = operator/(u);
					return *this;
				}

				Vector3 operator-()
				{
					Vector3 v = Vector3(*this);
					v.x = -v.x;
					v.y = -v.y;
					v.z = -v.z;
					return v;
				}

				Vector3 operator=(const Vector3& u)
				{
					Vector3 v = Vector3(u);
					return v;
				}

				bool operator==(const Vector3& u)
				{
					return (x == u.x) && (y == u.y) && (z == u.z);
				}

				bool operator<(const Vector3& u)
				{
					return ((x < u.x) && (y < u.y) && (z < u.z));
				}

				bool operator>(const Vector3& u)
				{
					return (!operator==(u) && !operator<(u));
				}

				bool operator<=(const Vector3& u)
				{
					return (operator==(u) || operator<(u));
				}

				bool operator>=(const Vector3& u)
				{
					return (operator==(u) || operator>(u));
				}

				bool operator!=(const Vector3& u)
				{
					return !operator==(u);
				}

				friend std::ostream& operator<<(std::ostream& out, const Vector3& u);

			private:
		};
	};
};

#endif