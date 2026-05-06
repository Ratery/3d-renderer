#pragma once

#include <array>

#include "Color.h"
#include "Linalg.h"

namespace renderer {

class Triangle {
   public:
    Triangle(const Matrix4x3& vertices, const Matrix4x3& normals,
             const std::array<Color, 3>& colors);

    Triangle(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& n0,
             const Vector4& n1, const Vector4& n2, const Color& c0, const Color& c1,
             const Color& c2);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0,
             const Vector3& n1, const Vector3& n2, const Color& c);

    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n,
             const Color& c);

    void transform(const Matrix4& matrix);

    void to_ndc();

    Vector4 vertex(Index index) const;
    Vector4 normal(Index index) const;
    Color color(Index index) const;

    const Matrix4x3& get_vertices() const;
    const Matrix4x3& get_normals() const;
    const std::array<Color, 3>& get_colors() const;

    Color get_weighted_color(Vector3 weights) const;

   private:
    Matrix4x3 vertices_;
    Matrix4x3 normals_;
    std::array<Color, 3> colors_;
};

}  // namespace renderer
