#include "scene/Object.h"

#include <utility>

namespace renderer {

Object::Object() : transform_matrix_(Matrix4::Identity()) {}

Object::Object(const Material& material) : material_(material) {}

Object::Object(std::vector<Triangle>&& triangles, const Matrix4& transform_matrix)
    : triangles_(std::move(triangles)), transform_matrix_(transform_matrix) {}

const std::vector<Triangle>& Object::get_triangles() const {
    return triangles_;
}

const Matrix4& Object::get_transform_matrix() const {
    return transform_matrix_;
}

const Material& Object::get_material() const {
    return material_;
}

void Object::set_material(const Material& material) {
    material_ = material;
}

void Object::add_triangle(const Triangle& triangle) {
    triangles_.push_back(triangle);
}

void Object::set_transform_matrix(const Matrix4& transform_matrix) {
    transform_matrix_ = transform_matrix;
}

}  // namespace renderer
