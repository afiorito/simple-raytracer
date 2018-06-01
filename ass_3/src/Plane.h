#ifndef ASS_3_SRC_PLANE_H_
#define ASS_3_SRC_PLANE_H_

#include "SceneObject.h"
#include <glm/glm.hpp>
using glm::vec3;

struct Plane: SceneObject {
    Plane();
    ~Plane();

    vec3 normal;

    vec3 normalAt(const vec3&) const;
    vec3 intersection(const Ray&) const;
};

#endif