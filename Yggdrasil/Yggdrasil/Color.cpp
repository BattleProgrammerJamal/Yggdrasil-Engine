#include "Color.hpp"

using namespace YG;
using namespace Math;

std::ostream& ::operator<<(std::ostream& out, const Color& u)
{
	out << "(" << u.r << "; " << u.g << "; " << u.b << ")";
	return out;
}