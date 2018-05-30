#include <iostream>
#include <glm/glm.hpp>
#include "Path.h"
#include "CImg.h"
using glm::vec3;
using namespace cimg_library;

int main() {

    int x = 1000;
    int y = 500;
    
    std::vector<unsigned char> data;
    CImg<unsigned char> image(200, 100, 1, 3, 0);

    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            vec3 color = vec3(float(i) / float(x), float(j) / float(y), 0.2);
            data.push_back(int(256.0 * color.r));
            data.push_back(int(256.0 * color.g));
            data.push_back(int(256.0 * color.b));
        }
    }

    // CImgDisplay main_disp(image, "Hello World!");

    // while(!main_disp.is_closed()) {
    //     main_disp.wait();
    // } 
    image.save(appendToSourcePath("/resources/test.bmp").c_str());

    std::cout << "Writing Complete!" << std::endl;

    return 0;
}