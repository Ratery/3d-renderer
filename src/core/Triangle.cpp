#include "Triangle.h"

namespace renderer {

Triangle::Triangle(const Matrix4x3& vertices, const Matrix4x3& normals,
                   const std::array<Color, 3>& colors)
    : vertices_(vertices), normals_(normals), colors_(colors) {}

Triangle::Triangle(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& n0,
                   const Vector4& n1, const Vector4& n2, const Color& c0, const Color& c1,
                   const Color& c2)
    : vertices_((Matrix4x3() << v0, v1, v2).finished()),
      normals_((Matrix4x3() << n0, n1, n2).finished()),
      colors_({c0, c1, c2}) {}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0,
                   const Vector3& n1, const Vector3& n2, const Color& c)
    : vertices_((Matrix4x3() << v0.homogeneous(), v1.homogeneous(), v2.homogeneous()).finished()),
      normals_((Matrix4x3() << n0.homogeneous(), n1.homogeneous(), n2.homogeneous()).finished()),
      colors_({c, c, c}) {
    normals_.row(3).setZero();
}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n,
                   const Color& c)
    : vertices_((Matrix4x3() << v0.homogeneous(), v1.homogeneous(), v2.homogeneous()).finished()),
      normals_((Matrix4x3() << n.homogeneous(), n.homogeneous(), n.homogeneous()).finished()),
      colors_({c, c, c}) {
    normals_.row(3).setZero();
}

void Triangle::transform(const Matrix4& matrix) {
    vertices_ = matrix * vertices_;
    normals_ = matrix * normals_;
}

void Triangle::to_ndc() {
    vertices_.array().rowwise() /= vertices_.row(3).array();
}

Vector4 Triangle::vertex(Index index) const {
    return vertices_.col(index);
}

Vector4 Triangle::normal(Index index) const {
    return normals_.col(index);
}

Color Triangle::color(Index index) const {
    return colors_[index];
}

const Matrix4x3& Triangle::get_vertices() const {
    return vertices_;
}

const Matrix4x3& Triangle::get_normals() const {
    return vertices_;
}

const std::array<Color, 3>& Triangle::get_colors() const {
    return colors_;
}

Color Triangle::get_weighted_color(Vector3 weights) const {
    return weights(0) * colors_[0] + weights(1) * colors_[1] + weights(2) * colors_[2];
}

}  // namespace renderer
