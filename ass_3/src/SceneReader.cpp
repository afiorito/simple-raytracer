#include "SceneReader.h"

SceneReader::SceneReader() {}
SceneReader::~SceneReader() {}

void SceneReader::loadScene(Scene& scene, const string& filepath) const {
    std::ifstream file(filepath);
    string line;
    
    getline(file, line);
    cout << "[file reader] - Reading " << line << " objects from file..." << endl;

    while (getline(file, line)) {
        if (line == "camera")
            loadCamera(scene.camera, file);
        if (line == "light")
            loadLight(scene.lights, file);
        if (line == "sphere")
            loadSphere(scene.objects, file);
        if (line == "plane")
            loadPlane(scene.objects, file);        
    }
}

void SceneReader::loadCamera(Camera& camera, std::ifstream& file) const {
    string pos; getline(file, pos);
    camera.position = parseVec3(pos);

    string fov; getline(file, fov);
    camera.fov = parseFloat(fov);

    string f; getline(file, f);
    camera.focal_length = parseFloat(f);

    string a; getline(file, a);
    camera.aspect_ratio = parseFloat(a);
}

void SceneReader::loadLight(vector<Light>& lights, std::ifstream& file) const {
    Light light;
    
    string pos; getline(file, pos);
    string col; getline(file, col);

    light.position = parseVec3(pos);
    light.color = parseVec3(col);

    lights.push_back(light);
}

void SceneReader::loadSphere(vector<SceneObject_s>& objects, std::ifstream& file) const {
    Sphere_s sphere = make_shared<Sphere>();

    string pos; getline(file, pos);
    sphere->position = parseVec3(pos);

    string rad; getline(file, rad);
    sphere->radius = parseFloat(rad);

    string amb; getline(file, amb);
    sphere->ambient = parseVec3(amb);

    string dif; getline(file, dif);
    sphere->diffuse = parseVec3(dif);

    string spe; getline(file, spe);
    sphere->specular = parseVec3(spe);

    string shi; getline(file, shi);
    sphere->shininess = parseFloat(shi);

    objects.push_back(sphere);
}

void SceneReader::loadPlane(vector<SceneObject_s>& objects, std::ifstream& file) const {
    Plane_s plane = make_shared<Plane>();

    string nor; getline(file, nor);
    plane->normal = parseVec3(nor);

    string pos; getline(file, pos);
    plane->position = parseVec3(pos);

    string amb; getline(file, amb);
    plane->ambient = parseVec3(amb);

    string dif; getline(file, dif);
    plane->diffuse = parseVec3(dif);

    string spe; getline(file, spe);
    plane->specular = parseVec3(spe);

    string shi; getline(file, shi);
    plane->shininess = parseFloat(shi);

    objects.push_back(plane);
}

vec3 SceneReader::parseVec3(const string& line) const {
    std::stringstream ss(line);
    vector<string> tokens = vector<string>{string_it(ss), string_it{}};

    return vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
}

float SceneReader::parseFloat(const string& line) const {
    std::stringstream ss(line);
    vector<string> tokens = vector<string>{string_it(ss), string_it{}};

    return stof(tokens[1]);
}