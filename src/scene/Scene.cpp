#include "scene/Scene.h"

#include <utility>

#include "scene/Object.h"

namespace renderer {

Scene::Scene(Camera&& camera) : camera_(std::move(camera)) {}

const std::vector<Object>& Scene::get_objects() const {
    return objects_;
}

void Scene::add_object(const Object& obj) {
    objects_.push_back(obj);
}

void Scene::add_object(Object&& obj) {
    objects_.push_back(std::move(obj));
}

Camera& Scene::camera() {
    return camera_;
}

const Camera& Scene::get_camera() const {
    return camera_;
}

const AmbientLight& Scene::get_ambient_light() const {
    return ambient_light_;
}

const std::vector<DirectionalLight>& Scene::get_directional_lights() const {
    return directional_lights_;
}

void Scene::set_ambient_light(const AmbientLight& light) {
    ambient_light_ = light;
}

void Scene::add_directional_light(const DirectionalLight& light) {
    directional_lights_.push_back(light);
}

}  // namespace renderer
