#ifndef YGGDRASIL_COLOR_HPP
#define YGGDRASIL_COLOR_HPP

#include <iostream>
#include <cmath>

namespace YG
{
	namespace Math
	{
		class Color
		{
			public:
				float r, g, b, a;

				Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
				{
					this->r = r;
					this->g = g;
					this->b = b;
					this->a = a;
				}

				Color(const Color& u)
				{
					this->r = u.r;
					this->g = u.g;
					this->b = u.b;
					this->a = u.a;
				}

				float length() 
				{ 
					return sqrt(r * r + g * g + b * b);
				}

				float lengthSq()
				{
					return (r * r + g * g + b * b);
				}

				float distance(Color& u)
				{
					return u.length() - length();
				}

				float distanceSq(Color& u)
				{
					return u.lengthSq() - lengthSq();
				}

				Color& normalize()
				{
					float l = length();
					r = r / l;
					g = g / l;
					b = b / l;
					return *this;
				}

				Color normalized()
				{
					float l = length();
					return Color(
						r / l,
						g / l,
						b / l
					);
				}

				float dot(const Color& u)
				{
					return (r * u.r) + (g * u.g) + (b * u.b);
				}

				Color cross(const Color& u)
				{
					return Color(
						(g * u.b) - (b * u.g),
						(b * u.r) - (r * u.b),
						(r * u.g) - (g * u.r)
					);
				}

				Color operator+(const Color& u)
				{
					Color v = Color(*this);
					v.r = v.r + u.r;
					v.g = v.g + u.g;
					v.b = v.b + u.b;
					return v;
				}

				Color& operator+=(const Color& u)
				{
					*this = operator+(u);
					return *this;
				}

				Color operator-(const Color& u)
				{
					Color v = Color(*this);
					v.r = v.r - u.r;
					v.g = v.g - u.g;
					v.b = v.b - u.b;
					return v;
				}

				Color& operator-=(const Color& u)
				{
					*this = operator-(u);
					return *this;
				}

				Color operator*(const Color& u)
				{
					Color v = Color(*this);
					v.r = v.r * u.r;
					v.g = v.g * u.g;
					v.b = v.b * u.b;
					return v;
				}

				Color& operator*=(const Color& u)
				{
					*this = operator*(u);
					return *this;
				}

				Color operator/(const Color& u)
				{
					Color v = Color(*this);
					v.r = v.r / (u.r == 0.0f ? 1.0f : u.r);
					v.g = v.g / (u.g == 0.0f ? 1.0f : u.g);
					v.b = v.b / (u.b == 0.0f ? 1.0f : u.b);
					return v;
				}

				Color& operator/=(const Color& u)
				{
					*this = operator/(u);
					return *this;
				}

				Color operator-()
				{
					Color v = Color(*this);
					v.r = -v.r;
					v.g = -v.g;
					v.b = -v.b;
					return v;
				}

				Color operator=(const Color& u)
				{
					Color v = Color(u);
					return v;
				}

				bool operator==(const Color& u)
				{
					return (r == u.r) && (g == u.g) && (b == u.b);
				}

				bool operator<(const Color& u)
				{
					return ((r < u.r) && (g < u.g) && (b < u.b));
				}

				bool operator>(const Color& u)
				{
					return (!operator==(u) && !operator<(u));
				}

				bool operator<=(const Color& u)
				{
					return (operator==(u) || operator<(u));
				}

				bool operator>=(const Color& u)
				{
					return (operator==(u) || operator>(u));
				}

				bool operator!=(const Color& u)
				{
					return !operator==(u);
				}

				friend std::ostream& operator<<(std::ostream& out, const Color& u);

			private:
		};
	};
};

#endif