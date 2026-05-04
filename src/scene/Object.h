#pragma once

#include <vector>

#include "core/Linalg.h"
#include "core/Triangle.h"

namespace renderer {

class Object {
   public:
    Object();
    Object(std::vector<Triangle>&& triangles, const Matrix4& transform_matrix);

    const std::vector<Triangle>& get_triangles() const;

    const Matrix4& get_transform_matrix() const;

    void add_triangle(const Triangle& triangle);

    // FIXME: rewrite
    void set_transform_matrix(const Matrix4& transform_matrix) { transform_matrix_ = transform_matrix; }

   private:
    std::vector<Triangle> triangles_;
    Matrix4 transform_matrix_;
};

}  // namespace renderer
