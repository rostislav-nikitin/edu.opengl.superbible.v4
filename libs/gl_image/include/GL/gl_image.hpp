#ifndef __GLIMAGE_GLIMAGE__
#define __GLIMAGE_GLIMAGE__

#include "image.hpp"

#include <GL/gl.h>

#include <memory>

namespace GlImage
{
// Definition
class GlImage
{
public:
	GlImage(std::unique_ptr<Image> image);

	auto getWidth() const -> GLint;
	auto getHeigth() const -> GLint;
	auto getComponents() const -> GLint;
	auto getFormat() const -> GLenum;
	auto getContent() const -> const char *;
private:
	std::unique_ptr<Image> image_;
};
}

#endif
