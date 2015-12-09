#include "Vector3.hpp"

using namespace YG;

std::ostream& ::operator<<(std::ostream& out, const Vector3& u)
{
	out << "(" << u.x << "; " << u.y << "; " << u.z << ")";
	return out;
}