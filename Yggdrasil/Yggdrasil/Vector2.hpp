#ifndef YGGDRASIL_VECTOR2_HPP
#define YGGDRASIL_VECTOR2_HPP

#include <iostream>
#include <cmath>

namespace YG
{
	class Vector2
	{
		public:
			float x, y;

			Vector2(float x = 0.0f, float y = 0.0f)
			{
				this->x = x;
				this->y = y;
			}

			Vector2(const Vector2& u)
			{
				this->x = u.x;
				this->y = u.y;
			}

			float length() 
			{ 
				return sqrt(x * x + y * y);
			}

			float lengthSq()
			{
				return (x * x + y * y);
			}

			float distance(Vector2& u)
			{
				return u.length() - length();
			}

			float distanceSq(Vector2& u)
			{
				return u.lengthSq() - lengthSq();
			}

			Vector2& normalize()
			{
				float l = length();
				x = x / l;
				y = y / l;
				return *this;
			}

			Vector2 normalized()
			{
				float l = length();
				return Vector2(
					x / l,
					y / l
				);
			}

			float dot(const Vector2& u)
			{
				return (x * u.x) + (y * u.y);
			}

			Vector2 cross(const Vector2& u)
			{
				return Vector2(
					(x * u.y) - (y * u.x),
					(y * u.x) - (x * u.y)
				);
			}

			Vector2 operator+(const Vector2& u)
			{
				Vector2 v = Vector2(*this);
				v.x = v.x + u.x;
				v.y = v.y + u.y;
				return v;
			}

			Vector2& operator+=(const Vector2& u)
			{
				*this = operator+(u);
				return *this;
			}

			Vector2 operator-(const Vector2& u)
			{
				Vector2 v = Vector2(*this);
				v.x = v.x - u.x;
				v.y = v.y - u.y;
				return v;
			}

			Vector2& operator-=(const Vector2& u)
			{
				*this = operator-(u);
				return *this;
			}

			Vector2 operator*(const Vector2& u)
			{
				Vector2 v = Vector2(*this);
				v.x = v.x * u.x;
				v.y = v.y * u.y;
				return v;
			}

			Vector2& operator*=(const Vector2& u)
			{
				*this = operator*(u);
				return *this;
			}

			Vector2 operator/(const Vector2& u)
			{
				Vector2 v = Vector2(*this);
				v.x = v.x / (u.x == 0.0f ? 1.0f : u.x);
				v.y = v.y / (u.y == 0.0f ? 1.0f : u.y);
				return v;
			}

			Vector2& operator/=(const Vector2& u)
			{
				*this = operator/(u);
				return *this;
			}

			Vector2 operator-()
			{
				Vector2 v = Vector2(*this);
				v.x = -v.x;
				v.y = -v.y;
				return v;
			}

			Vector2 operator=(const Vector2& u)
			{
				Vector2 v = Vector2(u);
				return v;
			}

			bool operator==(const Vector2& u)
			{
				return (x == u.x) && (y == u.y);
			}

			bool operator<(const Vector2& u)
			{
				return ((x < u.x) && (y < u.y));
			}

			bool operator>(const Vector2& u)
			{
				return (!operator==(u) && !operator<(u));
			}

			bool operator<=(const Vector2& u)
			{
				return (operator==(u) || operator<(u));
			}

			bool operator>=(const Vector2& u)
			{
				return (operator==(u) || operator>(u));
			}

			bool operator!=(const Vector2& u)
			{
				return !operator==(u);
			}

			friend std::ostream& operator<<(std::ostream& out, const Vector2& u);

		private:
	};
};

#endif