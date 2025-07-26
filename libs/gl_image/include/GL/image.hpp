#ifndef __GLIMAGE_IMAGE__
#define __GLIMAGE_IMAGE__

namespace GlImage
{
class Image
{
public:
	virtual auto getWidth() const -> int = 0;
	virtual auto getHeigth() const -> int = 0;
	virtual auto getColorDepth() const -> int = 0;
	virtual auto getContent() const -> const char * = 0;
};
}

#endif
