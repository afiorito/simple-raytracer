#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Path.h"
#include "CImg.h"
#include "SceneReader.h"
using glm::vec3;
using namespace cimg_library;

int main() {

    Scene scene;
    SceneReader reader;
    reader.loadScene(scene, appendToSourcePath("/resources/scenes/scene1.txt"));

    std::cout << "Objects: " << scene.objects.size() << std::endl;
    std::cout << "Lights: " << scene.lights.size() << std::endl;

    int x = 200;
    int y = 100;
    
    CImg<float> image(x, y, 1, 3, 0);

    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            vec3 color = vec3(float(i) / float(x), float(j) / float(y), 0.2f);
            image.draw_point(i, j, glm::value_ptr(color));
        }
    }

    // CImgDisplay main_disp(image, "Hello World!");

    // while(!main_disp.is_closed()) {
    //     main_disp.wait();
    // }

    image.normalize(0, 255);
    image.save(appendToSourcePath("/resources/test.bmp").c_str());

    std::cout << "Writing Complete!" << std::endl;

    return 0;
}