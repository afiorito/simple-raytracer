#ifndef ASS_3_SRC_SCENE_OBJECT_H_
#define ASS_3_SRC_SCENE_OBJECT_H_

#include "Ray.h"
#include <glm/glm.hpp>
using glm::vec3;

struct SceneObject {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    virtual ~SceneObject() {}

    virtual vec3 normalAt(const vec3&) const = 0;
    virtual float intersection(const Ray& ray) const = 0;
};

#endif