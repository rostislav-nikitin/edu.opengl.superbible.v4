#include "../include/GL/helpers.hpp"

namespace GlImage
{
auto getFileSize(std::ifstream &input) -> size_t
{
	input.seekg(0, std::ios_base::end);
	size_t result = input.tellg();
	input.seekg(0, std::ios_base::beg);

	return result;
}
}
