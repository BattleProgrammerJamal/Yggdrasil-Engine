#ifndef YGGDRASIL_QUATERNION_HPP
#define YGGDRASIL_QUATERNION_HPP

#include <iostream>
#include <cmath>

namespace YG
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

			Quaternion operator+(const Quaternion& u)
			{
				Quaternion v = Quaternion(*this);
				v.x = v.x + u.x;
				v.y = v.y + u.y;
				v.z = v.z + u.z;
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
				v.x = v.x * u.x;
				v.y = v.y * u.y;
				v.z = v.z * u.z;
				return v;
			}

			Quaternion& operator*=(const Quaternion& u)
			{
				*this = operator*(u);
				return *this;
			}

			Quaternion operator/(const Quaternion& u)
			{
				Quaternion v = Quaternion(*this);
				v.x = v.x / (u.x == 0.0f ? 1.0f : u.x);
				v.y = v.y / (u.y == 0.0f ? 1.0f : u.y);
				v.z = v.z / (u.z == 0.0f ? 1.0f : u.z);
				return v;
			}

			Quaternion& operator/=(const Quaternion& u)
			{
				*this = operator/(u);
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

			friend std::ostream& operator<<(std::ostream& out, const Quaternion& u);

		private:
	};
};

#endif