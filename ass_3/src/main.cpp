#include <glm/gtc/type_ptr.hpp>
#include "Helpers.h"
#include <iostream>
#include "Path.h"
#include "CImg.h"
#include "SceneReader.h"
using std::cout;
using std::endl;
using glm::vec3;
using cimg_library::CImg;
using cimg_library::CImgDisplay;
// #define DISPLAY

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

    std::string scene_name = "scene5";

    if (argc > 1)
        scene_name = argv[1];

    Scene scene;
    SceneReader reader;
    reader.loadScene(scene, appendToSourcePath("/resources/scenes/" + scene_name + ".txt"));

    CImg<float> image(scene.width(), scene.height(), 1, 3, 0);
    render(image, scene);

    #ifdef DISPLAY
        CImgDisplay main_disp(image, "COMP 371 - Assignment 3");

        while(!main_disp.is_closed()) {
            main_disp.wait();
        }
    #endif

    image.normalize(0, 255);
    image.save(appendToSourcePath("/resources/" + scene_name + ".bmp").c_str());

    return 0;
}

void render(CImg<float>& image, const Scene& scene) {
    // draw image from left -> right, top -> bottom
    Camera camera = scene.camera;
    float width = (float)scene.width(), height = (float)scene.height();
    vec3 top_right = vec3(-width / 2, height / 2, -camera.focal_length);

    for (int y = 0; y < scene.height(); y++) {
        for (int x = 0; x < scene.width(); x++) {
            float xCoord = float(x) / float(scene.width());
            float yCoord = float(y) / float(scene.height());

            Ray ray(camera.position, top_right + (xCoord * camera.kRIGHT * width) + (yCoord * camera.kDOWN * height));

            const vec3 c = color(ray, intersect(ray, scene.objects), scene);

            image.draw_point(x, y, glm::value_ptr(c));
        }
    }
}

const Intersection intersect(const Ray& ray, const vector<SceneObject_s>& objects) {
    float minimum = std::numeric_limits<float>::max();
    SceneObject_s closest;
    for (const SceneObject_s object : objects) {
        float t = object->intersection(ray);
        if (t > 0.00001f && t < minimum) {
            minimum = t;
            closest = object;
        }
    }

    return Intersection(minimum, closest);
}

vec3 color(const Ray& ray, const Intersection& i, const Scene& scene) {
    // if there was an intersection, return object color
    if (i.closest != nullptr) {
        vec3 color = i.closest->ambient;
        vec3 ipoint = ray.pointAt(i.t);
        vec3 normal = glm::normalize(i.closest->normalAt(ipoint));

        for (const Light& light : scene.lights) {
            vec3 light_dir = glm::normalize(light.position - ipoint);
            // fix shadow acne: https://stackoverflow.com/questions/23417736/ray-tracing-noise
            Ray s(ipoint + light_dir * 0.05f, light_dir);

            Intersection isect = intersect(s, scene.objects);

            float distance = glm::distance(light.position, s.pointAt(i.t));

            // if there was no intersection, object is lit
            if (isect.closest == nullptr) {
                float diffuse_light = glm::max(glm::dot(normal, light_dir), 0.0f);
                
                vec3 reflect_dir = glm::reflect(-light_dir, normal);
                float specular_light = glm::pow(glm::max(glm::dot(-ray.direction, reflect_dir), 0.0f), i.closest->shininess);

                vec3 diffuse = diffuse_light * i.closest->diffuse;
                vec3 specular = specular_light * i.closest->specular;

                color += (specular + diffuse) * light.color;
            }
        }

        return glm::clamp(color, 0.0f, 1.0f);
    }

    // if there was no intersection, return background color
    return backgroundColor(ray);
}

vec3 backgroundColor(const Ray& ray) {
    // normalize t between [0, 1]
    // float t = 0.5 * (ray.direction.y + 1.0f);
    // return (1.0f - t) * vec3(1.0f) + t * rgb(255.0f, 154.0f, 158.0f);
    return vec3(0.0f, 0.0f, 0.0f);
}