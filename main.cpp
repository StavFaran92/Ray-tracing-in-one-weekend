#include <iostream>

#include "ImageUtils.h"
#include "glm/glm.hpp"
#include "Ray.h"
#include "Color.h"

#define CHANNEL_NUM 3

bool hitSphere(const glm::vec3& center, float radius, const Ray& ray)
{
    glm::vec3 oc = ray.origin() - center;
    auto a = glm::dot(ray.direction(), ray.direction());
    auto b = 2.f * glm::dot(ray.direction(), oc);
    auto c = glm::dot(oc, oc) - radius * radius;
    return (b * b - 4 * a * c) > 0;

}

Color rayColor(const Ray& r) {
    if (hitSphere(glm::vec3(0, 0, -1), 0.5, r))
        return Color(1,0,0);
    glm::vec3 unit_direction = r.direction();
    float t = 0.5f * (unit_direction.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0f - t) + Color(0.5, 0.7, 1.0) * t;
}

int main() {

    

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    uint8_t* pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = glm::vec3(0, 0, 0);
    auto horizontal = glm::vec3(viewport_width, 0, 0);
    auto vertical = glm::vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length);
    

    // Render

    uint32_t index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = float(i) / (image_width - 1);
            auto v = float(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            auto color = rayColor(r);

            auto ir = static_cast<unsigned char>(color.r() * 255.999f);
            auto ig = static_cast<unsigned char>(255.999 * color.g());
            auto ib = static_cast<unsigned char>(255.999 * color.b());

            pixels[++index] = ir;
            pixels[++index] = ib;
            pixels[++index] = ig;
        }
    }

    ImageUtils::writeImage("test_image.png", image_width, image_height, pixels);

    system("test_image.png");

    std::cout << "\nDone.\n";
}