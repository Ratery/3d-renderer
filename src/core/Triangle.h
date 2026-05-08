#pragma once

#include "Linalg.h"

namespace renderer {

class Triangle {
   public:
    Triangle(const Matrix4x3& vertices, const Matrix4x3& normals);

    Triangle(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& n0,
             const Vector4& n1, const Vector4& n2);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0,
             const Vector3& n1, const Vector3& n2);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n);

    Vector4 vertex(Index index) const;
    Vector4 normal(Index index) const;

    const Matrix4x3& get_vertices() const;
    const Matrix4x3& get_normals() const;

   private:
    Matrix4x3 vertices_;
    Matrix4x3 normals_;
};

}  // namespace renderer
