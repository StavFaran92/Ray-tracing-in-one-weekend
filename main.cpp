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
#include "Material.h"
#include "ctpl_stl.h"
#include <future>
#include <chrono>

#define CHANNEL_NUM 3
#define NUM_OF_SAMPLES 50
#define MAX_DEPTH 50
#define IMAGE_WIDTH 600
#define IMAGE_HEIGHT 400
#define NUM_OF_THREADS 8

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
        return Color(1.0, 1.0, 1.0);
    }

    HitRecord rec;

    // We use 0.001 to avoid "Shadow Acne"
    if (world.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered))
        {
            return attenuation *rayColor(scattered, world, depth - 1);
        }
        return attenuation;
    }
    glm::vec3 unit_direction = r.direction();
    float t = 0.5f * (unit_direction.y + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0f - t) + Color(0.5, 0.7, 1.0) * t;
}

HittableList randomScene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            glm::vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color(randomDouble(), randomDouble(), randomDouble()) * Color(randomDouble(), randomDouble(), randomDouble());
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color(randomDouble(.5f, 1), randomDouble(.5f, 1), randomDouble(.5f, 1));
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));

    return world;
}

void renderPixel(int x, int y, int imageWidth, int imageHeight, const Camera& cam, const HittableList& world, uint8_t* pixels)
{
    Blend blender;
    for (int s = 0; s < NUM_OF_SAMPLES; s++)
    {
        auto u = float(x + randomDouble()) / (imageWidth - 1);
        auto v = (((imageHeight - 1) - float(y + randomDouble())) / (imageHeight - 1)); //Apply flip
        Ray& ray = cam.getRay(u, v);
        auto& color = rayColor(ray, world, MAX_DEPTH);

        blender.addColor(color);
    }
    Color& color = blender.getBlend();

    color.applyGammaCorrection(2.0f);

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    color.getAsUnsignedChar(r, g, b);

    int index = (y * imageWidth + x) * CHANNEL_NUM;

    pixels[++index] = r;
    pixels[++index] = b;
    pixels[++index] = g;
}

//void renderPixel(int x, int y, int imageWidth, int imageHeight, const Camera& cam, const HittableList& world, uint8_t* pixels)
//{
//    auto u = float(x) / (imageWidth - 1);
//    auto v = (((imageHeight-1) - float(y)) / (imageHeight - 1));
//
//    Color color(u, v, 0);
//
//    unsigned char r = 0;
//    unsigned char g = 0;
//    unsigned char b = 0;
//    color.getAsUnsignedChar(r, g, b);
//
//    int index = (y * imageWidth + x) * CHANNEL_NUM;
//
//    pixels[++index] = r;
//    pixels[++index] = b;
//    pixels[++index] = g;
//}

void displayProgress(float currVal, float maxVal, int& prevProgress)
{
    int progress = currVal / maxVal * 100;
    if (progress % 10 == 0)
    {
        if (progress != prevProgress)
        {
            std::cout << "\r" << progress << "%" << std::flush;
            prevProgress = progress;
        }
    }
}

int main() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Image
    const float aspectRatio = float(IMAGE_WIDTH) / IMAGE_HEIGHT;

    // Allocate buffer for image
    uint8_t* pixels = new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * CHANNEL_NUM];
    
    // World
    HittableList& world = randomScene();

    // Camera
    Camera cam(glm::vec3(6, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 90, aspectRatio);

    // Thread pool
    ctpl::thread_pool p(NUM_OF_THREADS);
    std::vector<std::future<void>> results(IMAGE_HEIGHT * IMAGE_WIDTH);

    std::cout << "Apply jobs:" << std::endl;

    // Render
    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        int previousProgress = 0;
        displayProgress(IMAGE_HEIGHT - j, IMAGE_HEIGHT, previousProgress);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            results[j * IMAGE_WIDTH + i] = p.push([&, i, j](int) 
            {
                renderPixel(i, j, IMAGE_WIDTH, IMAGE_HEIGHT, cam, world, pixels); 
            });
        }
    }

    std::cout << "\nProcess jobs:" << std::endl;

    // Sync threads
    for (int j = 0; j < results.size(); ++j) {
        results[j].get();
        int previousProgress = 0;
        displayProgress(j, results.size(), previousProgress);
    }

    // Write to image
    ImageUtils::writeImage("test_image.png", IMAGE_WIDTH, IMAGE_HEIGHT, pixels);

    // Deallocate image buffer
    //delete[] pixels;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Open image to view
    system("test_image.png");

    std::cout << std::endl;
    std::cout << "Overall Time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
    std::cout << "Done.\n";
}