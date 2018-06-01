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

void render(CImg<float>&, const Scene&);
vec3 color(const Ray&, const SceneObject_s);
vec3 backgroundColor(const Ray&);

int main() {

    Scene scene;
    SceneReader reader;
    reader.loadScene(scene, appendToSourcePath("/resources/scenes/scene1.txt"));

    std::cout << "Objects: " << scene.width() << std::endl;
    std::cout << "Lights: " << scene.height() << std::endl;

    CImg<float> image(scene.width(), scene.height(), 1, 3, 0);

    cout << scene.objects[1]->position.x << scene.objects[1]->position.y << scene.objects[1]->position.z << endl;

    render(image, scene);

    // int x = 200;
    // int y = 100;
    
    // CImg<float> image(x, y, 1, 3, 0);

    // for (int j = 0; j < y; j++) {
    //     for (int i = 0; i < x; i++) {
    //         vec3 color = vec3(float(i) / float(x), float(j) / float(y), 0.2f);
    //         image.draw_point(i, j, glm::value_ptr(color));
    //     }
    // }

    // CImgDisplay main_disp(image, "Hello World!");

    // while(!main_disp.is_closed()) {
    //     main_disp.wait();
    // }

    image.normalize(0, 255);
    image.save(appendToSourcePath("/resources/test.bmp").c_str());

    // std::cout << "Writing Complete!" << std::endl;

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

            Ray r(camera.position, top_right + (xCoord * camera.kRIGHT * width) + (yCoord * camera.kDOWN * height));
            vec3 c = color(r, scene.objects[1]);
            image.draw_point(x, y, glm::value_ptr(c));
        }
    }
}

vec3 color(const Ray& ray, const SceneObject_s object) {
    float t = object->intersection(ray);
    if (t > 0.0f) {
        vec3 normal = object->normalAt(ray.pointAt(t));

        return 0.5f * vec3(normal.x + 1, normal.y + 1, normal.z + 1);
    }

    return backgroundColor(ray);
}

vec3 backgroundColor(const Ray& ray) {
    // normalize t between [0, 1]
    float t = 0.5 * (ray.direction.y + 1.0f);

    return (1.0f - t) * vec3(1.0f) + t * rgb(255.0f, 154.0f, 158.0f);
}