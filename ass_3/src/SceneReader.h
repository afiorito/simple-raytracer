#ifndef ASS_3_SRC_SCENE_READER_H_
#define ASS_3_SRC_SCENE_READER_H_

#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::make_shared;

typedef std::istream_iterator<string> string_it;
typedef std::shared_ptr<Sphere> Sphere_s;
typedef std::shared_ptr<Plane> Plane_s;

class SceneReader {
    public:
        SceneReader();
        ~SceneReader();

        void loadScene(Scene&, const string&) const;
    
    private:
        void loadCamera(Camera&, std::ifstream&) const;
        void loadLight(vector<Light>&, std::ifstream&) const;
        void loadSphere(vector<SceneObject_s>&, std::ifstream&) const;
        void loadPlane(vector<SceneObject_s>&, std::ifstream&) const;
        vec3 parseVec3(const string&) const;
        float parseFloat(const string&) const;


};

#endif