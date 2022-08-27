#include <iostream>

#include "ImageUtils.h"
#include "glm/glm.hpp"
#include "Ray.h"
#include "Color.h"
#include "HittableList.h"
#include "Constants.h"
#include "Sphere.h"
#include "Camera.h"
#include "Utils.h"
#include "Blend.h"

#define CHANNEL_NUM 3

double hitSphere(const glm::vec3& center, float radius, const Ray& ray)
{
    glm::vec3 oc = ray.origin() - center;
    auto a = glm::dot(ray.direction(), ray.direction());
    auto b_half = glm::dot(ray.direction(), oc);
    auto c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b_half * b_half - a * c;
    if (discriminant < 0)
        return -1;
    else
        return (-b_half - glm::sqrt(discriminant)) / a;

}

Color rayColor(const Ray& r, const Hittable& world, int depth) {
    if (depth <= 0)
    {
        return Color(0,0,0);
    }

    HitRecord rec;

    // We use 0.001 to avoid "Shadow Acne"
    if (world.hit(r, 0.001, infinity, rec))
    {
        glm::vec3 target = rec.point + rec.normal + getUnitSphereRandomVec();
        return .5f * rayColor(Ray(rec.point, target - rec.point), world, depth - 1);
    }
    glm::vec3 unit_direction = r.direction();
    float t = 0.5f * (unit_direction.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0f - t) + Color(0.5, 0.7, 1.0) * t;
}

int main() {

    

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int numOfSamples = 100;
    const int maxDepth = 20;

    uint8_t* pixels = new uint8_t[image_width * image_height * CHANNEL_NUM];

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(glm::vec3{ 0,0,-1 }, 0.5));
    world.add(std::make_shared<Sphere>(glm::vec3{ 0,-100.5,-1 }, 100));

    // Camera
    Camera cam;    

    // Render

    uint32_t index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Blend blender;
            for (int s = 0; s < numOfSamples; s++)
            {
                auto u = float(i + randomDouble()) / (image_width - 1);
                auto v = float(j + randomDouble()) / (image_height - 1);
                Ray& ray = cam.getRay(u, v);
                auto& color = rayColor(ray, world, maxDepth);

                blender.add(color);
            }
            Color& color = blender.get();

            color.applyGammaCorrection(2.0f);

            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
            color.getAsUnsignedChar(r, g, b);

            pixels[++index] = r;
            pixels[++index] = b;
            pixels[++index] = g;
        }
    }

    ImageUtils::writeImage("test_image.png", image_width, image_height, pixels);

    system("test_image.png");

    std::cout << "\nDone.\n";
}