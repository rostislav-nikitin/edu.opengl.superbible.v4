#ifndef __GLIMAGE_GLI__
#define __GLIMAGE_GLI__

#include "tga_image.hpp"
#include "gl_image.hpp"

#include <filesystem>

namespace GlImage
{
	auto make_tga_image(std::filesystem::path filePath) -> GlImage;
}

#endif
