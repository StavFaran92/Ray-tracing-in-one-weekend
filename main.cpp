#include <iostream>

#include "stbi_wrapper.h"

#define CHANNEL_NUM 3

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
    uint8_t* pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];


    

    // Render

    uint32_t index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            auto ir = static_cast<unsigned char>(255.999 * r);
            auto ig = static_cast<unsigned char>(255.999 * g);
            auto ib = static_cast<unsigned char>(255.999 * b);

            pixels[++index] = ir;
            pixels[++index] = ib;
            pixels[++index] = ig;
        }
    }

    ImageIO::writeImage("test_image.png", image_width, image_height, pixels);

    system("test_image.png");

    std::cout << "\nDone.\n";
}