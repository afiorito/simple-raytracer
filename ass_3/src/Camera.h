#ifndef ASS_3_SRC_CAMERA_H_
#define ASS_3_SRC_CAMERA_H_


#include <glm/glm.hpp>
#include "SceneObject.h"
using glm::vec3;

struct Camera {
    // Camera orientation vectors
    const vec3 kDIRECTION = vec3(0.0f, 0.0f, -1.0f);
    const vec3 kDOWN = vec3(0.0f, -1.0f, 0.0f);
    const vec3 kRIGHT = vec3(1.0f, 0.0f, 0.0f);

    vec3 position;  
    float fov;
    float focal_length;
    float aspect_ratio;
};

#endif