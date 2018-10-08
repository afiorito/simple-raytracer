#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

#include <glm/glm.hpp>
using glm::vec3;

struct Light {
    vec3 position;
    vec3 color;
};

#endif