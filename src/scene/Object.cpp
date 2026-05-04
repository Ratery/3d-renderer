#include "Object.h"

#include <utility>

namespace renderer {

Object::Object() : transform_matrix_(Matrix4::Identity()) {}

Object::Object(std::vector<Triangle>&& triangles, const Matrix4& transform_matrix)
    : triangles_(std::move(triangles)), transform_matrix_(transform_matrix) {}

const std::vector<Triangle>& Object::get_triangles() const {
    return triangles_;
}

const Matrix4& Object::get_transform_matrix() const {
    return transform_matrix_;
}

void Object::add_triangle(const Triangle& triangle) {
    triangles_.push_back(triangle);
}

}  // namespace renderer
