#include "Plane.h"

Plane::Plane() {}
Plane::~Plane() {}

vec3 Plane::normalAt(const vec3& point) const {
    return normal;
}

/// Determines the intersection for plane with formula:
/// ax + by + cz + d = 0
float Plane::intersection(const Ray& ray) const {
    float nd = glm::dot(normal, ray.direction);

    if (nd == 0) return -1.0f;

    return glm::dot(position - ray.origin, normal) / nd;
}