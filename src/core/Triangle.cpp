#include "core/Triangle.h"

namespace renderer {

Triangle::Triangle(const Matrix4x3& vertices, const Matrix4x3& normals, const Matrix2x3& uvs)
    : vertices_(vertices), normals_(normals), uvs_(uvs) {
    normals_.row(3).setZero();
}

Triangle::Triangle(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& n0,
                   const Vector4& n1, const Vector4& n2, const Vector2& uv0, const Vector2& uv1,
                   const Vector2& uv2)
    : vertices_((Matrix4x3() << v0, v1, v2).finished()),
      normals_((Matrix4x3() << n0, n1, n2).finished()),
      uvs_((Matrix2x3() << uv0, uv1, uv2).finished()) {
    normals_.row(3).setZero();
}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0,
                   const Vector3& n1, const Vector3& n2, const Vector2& uv0, const Vector2& uv1,
                   const Vector2& uv2)
    : vertices_((Matrix4x3() << v0.homogeneous(), v1.homogeneous(), v2.homogeneous()).finished()),
      normals_((Matrix4x3() << n0.homogeneous(), n1.homogeneous(), n2.homogeneous()).finished()),
      uvs_((Matrix2x3() << uv0, uv1, uv2).finished()) {
    normals_.row(3).setZero();
}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n,
                   const Vector2& uv0, const Vector2& uv1, const Vector2& uv2)
    : vertices_((Matrix4x3() << v0.homogeneous(), v1.homogeneous(), v2.homogeneous()).finished()),
      normals_((Matrix4x3() << n.homogeneous(), n.homogeneous(), n.homogeneous()).finished()),
      uvs_((Matrix2x3() << uv0, uv1, uv2).finished()) {
    normals_.row(3).setZero();
}

Vector4 Triangle::vertex(Index index) const {
    return vertices_.col(index);
}

Vector4 Triangle::normal(Index index) const {
    return normals_.col(index);
}

Vector2 Triangle::uv(Index index) const {
    return uvs_.col(index);
}

const Matrix4x3& Triangle::get_vertices() const {
    return vertices_;
}

const Matrix4x3& Triangle::get_normals() const {
    return normals_;
}

const Matrix2x3& Triangle::get_uvs() const {
    return uvs_;
}

}  // namespace renderer
