#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {
    
}

int Scene::width() const {
        return 2 * camera.focal_length * glm::tan(glm::radians(camera.fov / 2));
    }

int Scene::height() const {
    return width() / camera.aspect_ratio;
}