#ifndef __GLIMAGE_HELPERS__
#define __GLIMAGE_HELPERS__

#include <cstddef>
#include <filesystem>
#include <fstream>

namespace GlImage
{
	auto getFileSize(std::ifstream &input) -> size_t;
}

#endif
