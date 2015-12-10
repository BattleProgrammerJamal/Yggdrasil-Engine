#include "Matrix4.hpp"

using namespace YG;
using namespace Math;

std::ostream& ::operator<<(std::ostream& out, Matrix4& m)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			unsigned int index = j + i * 4;
			out << m[index] << " ";
		}
		out << std::endl;
	}
	return out;
}