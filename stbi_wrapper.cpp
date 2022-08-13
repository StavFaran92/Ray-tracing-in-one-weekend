#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "stbi_wrapper.h"
#include "stb_image_write.h"

void ImageIO::writeImage(const char* filename, int w, int h, const void* data)
{
	stbi_write_png(filename, w, h, 3, data, w * 3);
}
