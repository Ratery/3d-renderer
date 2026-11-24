#pragma once

#include <Eigen/Dense>

namespace renderer {

using Index = Eigen::Index;

using Vector2 = Eigen::Vector2f;
using Vector3 = Eigen::Vector3f;
using Vector4 = Eigen::Vector4f;

using Matrix3 = Eigen::Matrix3f;
using Matrix4 = Eigen::Matrix4f;
using Matrix2x3 = Eigen::Matrix<float, 2, 3>;
using Matrix4x3 = Eigen::Matrix<float, 4, 3>;

inline Matrix4 make_translation_matrix(const Vector3& translation) {
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translate(translation);
    return transform.matrix();
}

inline Matrix4 make_rotation_matrix(const Vector3& axis, float angle) {
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.rotate(Eigen::AngleAxisf(angle, axis.normalized()));
    return transform.matrix();
}

}  // namespace renderer
