#ifndef SRC_SPHERE_H_
#define SRC_SPHERE_H_

#include "SceneObject.h"
#include <glm/glm.hpp>
using glm::vec3;

struct Sphere: SceneObject {

    Sphere();
    ~Sphere();

    float radius;

    vec3 normalAt(const vec3&) const;
    float intersection(const Ray&) const;
};

#endif