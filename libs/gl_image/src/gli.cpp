#include "../include/GL/gli.hpp"

#include <memory>

namespace GlImage
{
	auto make_tga_image(std::filesystem::path filePath) -> GlImage
	{
		return GlImage{std::make_unique<TgaImage>(filePath)};
	}
}
