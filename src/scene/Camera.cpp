#include "Camera.h"

#include <cmath>

namespace renderer {

Camera::Camera(float near, float far, float fov)
    : near_(near),
      far_(far),
      fov_(fov),
      view_matrix_(Matrix4::Identity()) {}

const Matrix4& Camera::get_view_matrix() const {
    return view_matrix_;
}

Matrix4 Camera::make_projection_matrix(float aspect_ratio) const {  // TODO: split into make() and get() methods
    float right = near_ * std::tan(fov_ / 2.0f);
    float top = right * aspect_ratio;
    return Matrix4{
        {near_ / right, 0.0f, 0.0f, 0.0f},
        {0.0f, near_ / top, 0.0f, 0.0f},
        {0.0f, 0.0f, (far_ + near_) / (far_ - near_), -2.0f * near_ * far_ / (far_ - near_)},
        {0.0f, 0.0f, 1.0f, 0.0f}};
}

void Camera::move_forward(float distance) {
    Vector3 translation = distance * Vector3::UnitZ();
    view_matrix_ = make_translation_matrix(-translation) * view_matrix_;  // V' = T^(-1) * V
}

void Camera::move_backward(float distance) {
    move_forward(-distance);
}

void Camera::move_right(float distance) {
    Vector3 translation = distance * Vector3::UnitX();
    view_matrix_ = make_translation_matrix(-translation) * view_matrix_;
}

void Camera::move_left(float distance) {
    move_right(-distance);
}

void Camera::move_up(float distance) {
    Vector3 translation = distance * get_world_up_vector();
    view_matrix_ = make_translation_matrix(-translation) * view_matrix_;
}

void Camera::move_down(float distance) {
    move_up(-distance);
}

void Camera::rotate_horizontal(float angle) {
    view_matrix_ = make_rotation_matrix(get_world_up_vector(), -angle) * view_matrix_;
}

void Camera::rotate_vertical(float angle) {
    view_matrix_ = make_rotation_matrix(Vector3::UnitX(), -angle) * view_matrix_;
}

Vector3 Camera::get_world_up_vector() const {
    return view_matrix_.col(1).head<3>().normalized();
}

}  // namespace renderer
