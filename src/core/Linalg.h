#pragma once

#include <Eigen/Dense>

namespace renderer {

using Index = Eigen::Index;

template<typename T, int size>
using Vector = Eigen::Vector<T, size>;

using Vector2 = Eigen::Vector2f;
using Vector3 = Eigen::Vector3f;
using Vector4 = Eigen::Vector4f;

using Matrix3 = Eigen::Matrix3f;
using Matrix4 = Eigen::Matrix4f;
using Matrix4x3 = Eigen::Matrix<float, 4, 3>;

}  // namespace renderer
