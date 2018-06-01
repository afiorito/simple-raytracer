#ifndef ASS_3_SRC_RAY_H_
#define ASS_3_SRC_RAY_H_

#include <glm/glm.hpp>
using glm::vec3;

struct Ray {
    vec3 origin;
    vec3 direction;

    Ray(vec3, vec3);

    const vec3 pointAt(float) const;

};

#endif