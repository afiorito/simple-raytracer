#ifndef SRC_HELPERS_H_
#define SRC_HELPERS_H_

#include <glm/glm.hpp>
using glm::vec3;

/// Convert a color value from [0, 255] ==> [0.0, 1.0]
vec3 rgb(vec3 color) {
    return vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

/// Convert a color value from [0, 255] ==> [0.0, 1.0]
vec3 rgb(float r, float g, float b) {
    return rgb(vec3(r, g, b));
}

#endif