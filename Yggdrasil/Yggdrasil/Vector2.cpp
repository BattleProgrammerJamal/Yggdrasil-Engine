#include "Vector2.hpp"

using namespace YG;
using namespace Math;

std::ostream& ::operator<<(std::ostream& out, const Vector2& u)
{
	out << "(" << u.x << "; " << u.y << ")";
	return out;
}