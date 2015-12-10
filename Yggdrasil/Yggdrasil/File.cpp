#include "File.hpp"

using namespace YG;

std::ostream& ::operator<<(std::ostream& out, File& file)
{
	std::vector<std::string> lines = file.getContent();
	static unsigned int cursor = 0;
	out << lines.at(cursor);
	cursor = (cursor + 1) % lines.size();
	return out;
}