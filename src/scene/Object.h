#pragma once

#include <vector>

#include "core/Linalg.h"
#include "core/Triangle.h"
#include "rendering/material/Material.h"

namespace renderer {

class Object {
   public:
    Object();
    explicit Object(const Material& material);
    Object(std::vector<Triangle>&& triangles, const Matrix4& transform_matrix);

    const std::vector<Triangle>& get_triangles() const;

    const Matrix4& get_transform_matrix() const;

    const Material& get_material() const;
    void set_material(const Material& material);

    void add_triangle(const Triangle& triangle);

    void set_transform_matrix(const Matrix4& transform_matrix);

   private:
    std::vector<Triangle> triangles_;
    Matrix4 transform_matrix_;
    Material material_;
};

}  // namespace renderer
