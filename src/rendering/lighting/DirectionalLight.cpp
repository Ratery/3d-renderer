#include "rendering/lighting/DirectionalLight.h"

namespace renderer {

DirectionalLight::DirectionalLight(const Color& intensity, const Vector3& direction)
    : intensity_(intensity), direction_(direction.normalized()) {}

const Color& DirectionalLight::get_intensity() const {
    return intensity_;
}

void DirectionalLight::set_intensity(const Color& intensity) {
    intensity_ = intensity;
}

const Vector3& DirectionalLight::get_direction() const {
    return direction_;
}

void DirectionalLight::set_direction(const Vector3& direction) {
    direction_ = direction.normalized();
}

DirectionalLight DirectionalLight::make_transformed(const Matrix4& matrix) const {
    auto transformed_dir = matrix.topLeftCorner<3, 3>() * direction_;
    return {intensity_, transformed_dir.normalized()};
}

}  // namespace renderer
