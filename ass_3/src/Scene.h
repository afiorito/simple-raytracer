#ifndef ASS_3_SRC_SCENE_H_
#define ASS_3_SRC_SCENE_H_

#include "Camera.h"
#include "Light.h"
#include "SceneObject.h"
#include <vector>
using std::vector;

typedef std::shared_ptr<SceneObject> SceneObject_s;

struct Scene {
    Camera camera;
    vector<SceneObject_s> objects;
    vector<Light> lights;
    
    Scene();
    ~Scene();

    int height() const;
    int width() const;

};

#endif