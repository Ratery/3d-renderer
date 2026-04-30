#include "Scene.h"

#include <utility>

#include "Object.h"

namespace renderer {

Scene::Scene(const Camera& camera) : camera_(camera) {}

const std::vector<Object>& Scene::get_objects() const {
    return objects_;
}

void Scene::add_object(const Object& obj) {
    objects_.push_back(obj);
}

void Scene::add_object(Object&& obj) {
    objects_.push_back(std::move(obj));
}

Camera& Scene::get_camera() {
    return camera_;
}

const Camera& Scene::get_camera() const {
    return camera_;
}

}  // namespace renderer
