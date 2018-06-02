#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {
    
}

int Scene::width() const {
        return height() * camera.aspect_ratio;
    }

int Scene::height() const {
    return 2 * camera.focal_length * glm::tan(glm::radians(camera.fov / 2));
}