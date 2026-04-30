#pragma once

#include <Eigen/Dense>

namespace renderer {

constexpr float EPS = 1e-5f;

using Vector2 = Eigen::Vector2f;
using Vector3 = Eigen::Vector3f;
using Vector4 = Eigen::Vector4f;

using Matrix3 = Eigen::Matrix3f;
using Matrix4 = Eigen::Matrix4f;

}  // namespace renderer
