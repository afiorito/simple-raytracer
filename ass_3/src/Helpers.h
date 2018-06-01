#ifndef ASS_3_SRC_HELPERS_H_
#define ASS_3_SRC_HELPERS_H_

#include <glm/glm.hpp>
using glm::vec3;

vec3 rgb(vec3 color) {
    return vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

vec3 rgb(float r, float g, float b) {
    return rgb(vec3(r, g, b));
}

#endif