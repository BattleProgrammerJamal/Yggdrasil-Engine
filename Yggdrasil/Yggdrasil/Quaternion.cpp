#include "Quaternion.hpp"

using namespace YG;
using namespace Math;

std::ostream& ::operator<<(std::ostream& out, const Quaternion& u)
{
	out << "(" << u.x << "; " << u.y << "; " << u.z << "; " << u.w << ")";
	return out;
}