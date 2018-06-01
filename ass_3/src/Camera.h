#ifndef ASS_3_SRC_CAMERA_H_
#define ASS_3_SRC_CAMERA_H_


#include <glm/glm.hpp>
#include "SceneObject.h"
using glm::vec3;

struct Camera {
    vec3 position;  
    float fov;
    float focal_length;
    float aspect_ratio;
};

#endif