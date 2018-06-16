#include <glm/gtc/type_ptr.hpp>
#include "Helpers.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Path.h"
#include "CImg.h"
#include "SceneReader.h"
using std::cout;
using std::endl;
using std::string;
using glm::vec3;
using cimg_library::CImg;
using cimg_library::CImgDisplay;

// MARK: DEFINES
// Determines the number of samples for antialiasing
// Set to 1 to disable antialiasing
#define NUMBER_OF_SAMPLES 10
typedef std::chrono::high_resolution_clock clk;

// Container for storing ray intersection data
struct Intersection {
    float t;
    SceneObject_s closest;

    Intersection(float t, SceneObject_s closest): t(t), closest(closest) {}
};

void render(CImg<float>&, const Scene&);
const Intersection intersect(const Ray&, const vector<SceneObject_s>&);
vec3 color(const Ray&, const Intersection&, const Scene&);
vec3 backgroundColor(const Ray&);

int main(int argc, char* argv[]) {
    // user input variables
    string scene_name = "scene5";
    bool draw_to_screen = false;

    // user input
    if (argc > 1) scene_name = argv[1];
    if (argc > 2) draw_to_screen = true;

    Scene scene;
    SceneReader reader;
    reader.loadScene(scene, appendToSourcePath("/resources/scenes/" + scene_name + ".txt"));

    cout << "[ray trace] - started image render." << endl;
    auto start = clk::now();
    
    // Create a CImg image to store color values
    CImg<float> image(scene.width(), scene.height(), 1, 3, 0);
    render(image, scene);
    
    std::chrono::duration<float> duration = clk::now() - start;
    cout << "[ray trace] - completed image render in " << duration.count() << "s." << endl;

    if (draw_to_screen) {
        CImgDisplay main_disp(image, "COMP 371 - Assignment 3");

        while(!main_disp.is_closed()) {
            main_disp.wait();
        }
    }

    // Normalize image to 8 bit char values before saving
    // This is needed since CImg image stores float values
    // Need to convert from [0.0, 1.0] ==> [0, 255]
    image.normalize(0, 255);
    image.save(appendToSourcePath("/resources/" + scene_name + ".bmp").c_str());

    return 0;
}

/// render the raytraced image to CImg image
void render(CImg<float>& image, const Scene& scene) {
    // draw image from left -> right, top -> bottom
    Camera camera = scene.camera;
    float width = (float)scene.width(), height = (float)scene.height();
    vec3 top_left = vec3(-width / 2, height / 2, -camera.focal_length);

    // for each pixel (x, y)
    for (int y = 0; y < scene.height(); y++) {
        for (int x = 0; x < scene.width(); x++) {
            vec3 accumulatedColor = vec3(0.0f);
            for (int i = 0; i < NUMBER_OF_SAMPLES; i++) {
                // if antialiasing is enabled, need to add offset to x and y values
                float modifier = NUMBER_OF_SAMPLES > 1 ? drand48() : 0.0f; 
                float xCoord = float(x + modifier) / width;
                float yCoord = float(y + modifier) / height;

                // Generate intersection ray
                Ray ray(camera.position, top_left + (xCoord * camera.kRIGHT * width) + (yCoord * camera.kDOWN * height));

                accumulatedColor += color(ray, intersect(ray, scene.objects), scene);
            }

            // take average from pixel samples
            accumulatedColor /= float(NUMBER_OF_SAMPLES);

            image.draw_point(x, y, glm::value_ptr(accumulatedColor));
        }
    }
}

/// Find a ray intersection with a list of objects
/// if no object is hit, intersection.closest will be nullptr
const Intersection intersect(const Ray& ray, const vector<SceneObject_s>& objects) {
    float minimum = std::numeric_limits<float>::max();
    SceneObject_s closest;
    for (const SceneObject_s object : objects) {
        float t = object->intersection(ray);
        // use bias value for t, reduces shadow acne
        if (t > 0.015f && t < minimum) {
            minimum = t;
            closest = object;
        }
    }

    return Intersection(minimum, closest);
}

/// Compute the color of a pixel using the phong illumination model
/// If there is an intersection:
///   1. Determine the intersection point and normal
///   2. Loop through all lights in the scene:
///     - if there is no intersection or intersection is behind the light
///        compute phong lighting
///     - if there is an intersection, object is in shadow
///   3. Add color contribution from all lights
///   4. Clamp color value between [0.0, 1.0]   
/// If there is no intersection:
///   1. Return background color
vec3 color(const Ray& ray, const Intersection& i, const Scene& scene) {
    // if there was an intersection, return object color
    if (i.closest != nullptr) {
        // intersection point and normal
        vec3 color = i.closest->ambient;
        vec3 ipoint = ray.pointAt(i.t);
        vec3 normal = glm::normalize(i.closest->normalAt(ipoint));

        for (const Light& light : scene.lights) {
            vec3 light_dir = glm::normalize(light.position - ipoint);
            Ray s(ipoint, light_dir);

            const Intersection isect = intersect(s, scene.objects);
            float light_dist = glm::distance(light.position, ipoint);
            float block_dist = glm::distance(s.pointAt(isect.t), ipoint);

            // if there was no intersection, object is lit
            if (isect.closest == nullptr || block_dist > light_dist) {
                // Diffuse component
                float diffuse_light = glm::max(glm::dot(normal, light_dir), 0.0f);
                
                // Specular component
                vec3 reflect_dir = glm::reflect(-light_dir, normal);
                float specular_light = glm::pow(glm::max(glm::dot(-ray.direction, reflect_dir), 0.0f), i.closest->shininess);

                vec3 diffuse = diffuse_light * i.closest->diffuse;
                vec3 specular = specular_light * i.closest->specular;

                // Phong = ambient + light.color * (specular + diffuse)
                color += (specular + diffuse) * light.color;
            }
        }

        return glm::clamp(color, 0.0f, 1.0f);
    }

    // if there was no intersection, return background color
    return backgroundColor(ray);
}

vec3 backgroundColor(const Ray& ray) {
    return vec3(0.0f, 0.0f, 0.0f);
}