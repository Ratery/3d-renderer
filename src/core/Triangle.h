#pragma once

#include "core/Linalg.h"

namespace renderer {

class Triangle {
   public:
    Triangle(const Matrix4x3& vertices, const Matrix4x3& normals, const Matrix2x3& uvs);

    Triangle(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& n0,
             const Vector4& n1, const Vector4& n2, const Vector2& uv0, const Vector2& uv1,
             const Vector2& uv2);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0,
             const Vector3& n1, const Vector3& n2, const Vector2& uv0, const Vector2& uv1,
             const Vector2& uv2);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n,
             const Vector2& uv0, const Vector2& uv1, const Vector2& uv2);

    Vector3 vertex3(Index index) const;
    Vector3 normal3(Index index) const;
    Vector4 vertex4(Index index) const;
    Vector4 normal4(Index index) const;
    Vector2 uv(Index index) const;
    const Vector4& face_normal() const;

    const Matrix4x3& get_vertices() const;
    const Matrix4x3& get_normals() const;
    const Matrix2x3& get_uvs() const;

   private:
    Matrix4x3 vertices_;
    Matrix4x3 normals_;
    Matrix2x3 uvs_;
    Vector4 face_normal_;

    Vector4 compute_face_normal() const;
};

}  // namespace renderer
