#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "ImageUtils.h"
#include "stb_image_write.h"

void ImageUtils::writeImage(const char* filename, int w, int h, const void* data)
{
	stbi_write_png(filename, w, h, 3, data, w * 3);
}
