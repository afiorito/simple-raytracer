#include "Sphere.h"

Sphere::Sphere() {}

Sphere::~Sphere() {}

vec3 Sphere::normalAt(const vec3& point) const {
    vec3 normal = glm::normalize(point - position);

    return normal;
}

float Sphere::intersection(const Ray& ray) const {
    vec3 rc = ray.origin - position;
    
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(rc, ray.direction);
    float c = glm::dot(rc, rc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    return discriminant < 0.0f ? -1.0f : (-b - glm::sqrt(discriminant)) / (2.0 * a);
}
