#include "Ray.h"

Ray::Ray(vec3 origin, vec3 direction): origin(origin), direction(glm::normalize(direction)) {}

const vec3 Ray::pointAt(float t) const {
    return origin + direction * t;
}   