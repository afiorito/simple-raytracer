#include "Sphere.h"

Sphere::Sphere() {}

Sphere::~Sphere() {}

vec3 Sphere::normalAt(const vec3& point) const {
    vec3 normal = glm::normalize(point - position);

    return normal;
}

/// Compute an intersection for a sphere with formula:
/// x² + y² + z² = r²
float Sphere::intersection(const Ray& ray) const {
    vec3 rc = ray.origin - position;
    
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(rc, ray.direction);
    float c = glm::dot(rc, rc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return -1.0f;

    float t0 = (-b - glm::sqrt(discriminant)) / (2 * a);
    float t1 = (-b + glm::sqrt(discriminant)) / (2 * a);

    return glm::min(t0, t1);

}
