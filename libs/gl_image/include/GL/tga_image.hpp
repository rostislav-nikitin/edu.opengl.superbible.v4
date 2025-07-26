#ifndef __GLIMAGE_TGAIMAGE__
#define __GLIMAGE_TGAIMAGE__

#include "image.hpp"

#include <cstdint>
#include <vector>
#include <filesystem>

namespace GlImage
{
struct __attribute__((packed)) TgaHeader
{
	uint8_t idSize;
	uint8_t colorMapType;
	uint8_t imageType;
	// Color map description
	uint16_t firstElementIndex;
	uint16_t colorMapLength;
	uint8_t colorMapElementSize;
	// Image Description
	uint16_t xOrigin;
	uint16_t yOrigin;
	uint16_t width;
	uint16_t heigth;
	uint8_t colorDepth;
	uint8_t imageDescriptor;
};

// Definition
class TgaImage : public Image
{
public:
	TgaImage() = default;
	TgaImage(std::filesystem::path filePath);

	auto load(std::filesystem::path filePath) -> void;
	auto getIsLoaded() const -> bool;
	auto getSize() const -> size_t;

	auto getWidth() const -> int override;
	auto getHeigth() const -> int override;
	auto getColorDepth() const -> int override;
	auto getContent() const -> const char * override;

private:
	std::filesystem::path filePath_;
	bool isLoaded_{};
	TgaHeader header_{};
	std::vector<char> content_{};
private:
	auto loadFile() -> void;
};
}

#endif
