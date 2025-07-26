#include "../include/GL/gl_image.hpp"

#include <GL/gl.h>

#include <cassert>
#include <memory>

namespace GlImage
{
GlImage::GlImage(std::unique_ptr<Image> image) : image_{std::move(image)}
{
}
auto GlImage::getWidth() const -> GLint
{
	return static_cast<GLint>(image_->getWidth());
}
auto GlImage::getHeigth() const -> GLint
{
	return static_cast<GLint>(image_->getHeigth());
}
auto GlImage::getComponents() const -> GLint
{
	assert(image_->getColorDepth() == 8 || image_->getColorDepth() == 24 || image_->getColorDepth() == 32);
	switch(image_->getColorDepth())
	{
		case 8:
			return GL_LUMINANCE8;
		case 24:
			return GL_RGB8;
		case 32:
			return GL_RGBA8;
		default:
			return 0;
	}
}
auto GlImage::getFormat() const -> GLenum
{
	assert(image_->getColorDepth() == 8 || image_->getColorDepth() == 24 || image_->getColorDepth() == 32);
	switch(image_->getColorDepth())
	{
		case 8:
			return GL_LUMINANCE;
		case 24:
			return GL_BGR_EXT;
		case 32:
			return GL_BGRA_EXT;
		default:
			return 0;
	}
}
auto GlImage::getContent() const -> const char *
{
	return image_->getContent();
}
}
