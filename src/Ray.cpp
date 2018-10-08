#include "Ray.h"

Ray::Ray(vec3 origin, vec3 direction): origin(origin), direction(glm::normalize(direction)) {}

/// Compute the point along a ray
const vec3 Ray::pointAt(float t) const {
    return origin + direction * t;
}   