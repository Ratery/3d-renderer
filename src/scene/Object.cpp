#include "Object.h"

namespace renderer {

Object::Object(const std::vector<Triangle>& triangles, const Matrix4& transform_matrix)
    : triangles_(triangles), transform_matrix_(transform_matrix) {}

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
