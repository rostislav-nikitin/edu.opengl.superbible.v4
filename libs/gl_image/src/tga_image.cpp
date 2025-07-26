#include "../include/GL/tga_image.hpp"

#include "../include/GL/helpers.hpp"

#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace GlImage
{
TgaImage::TgaImage(std::filesystem::path filePath) : filePath_{filePath}
{
	load(filePath);
}
auto TgaImage::getIsLoaded() const -> bool
{
	return isLoaded_;
}
auto TgaImage::getSize() const -> size_t
{
	return content_.size();
}
auto TgaImage::load(std::filesystem::path filePath) -> void
{
	filePath_ = std::move(filePath);
	loadFile();
	isLoaded_ = true;
}
auto TgaImage::loadFile() -> void
{
	std::ifstream input{filePath_, std::ios::binary};
	size_t fileSize = getFileSize(input);
	assert(fileSize >= sizeof(TgaHeader));
	// Read header
	std::istreambuf_iterator<char> iter{input};
	std::copy_n(iter, sizeof(TgaHeader), reinterpret_cast<char *>(&header_));
	// Read image content
	content_.reserve(fileSize - sizeof(TgaHeader));
	std::copy(iter, std::istreambuf_iterator<char>(), std::back_inserter(content_));
}
auto TgaImage::getWidth() const -> int
{
	assert(true == isLoaded_);

	return header_.width;
}
auto TgaImage::getHeigth() const -> int
{
	assert(true == isLoaded_);

	return header_.heigth;
}
auto TgaImage::getColorDepth() const -> int
{
	assert(true == isLoaded_);

	return header_.colorDepth;
}
auto TgaImage::getContent() const -> const char *
{
	return content_.data();
}
}
