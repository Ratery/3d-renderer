#include "rendering/lighting/AmbientLight.h"

namespace renderer {

AmbientLight::AmbientLight(const Color& intensity) : intensity_(intensity) {}

const Color& AmbientLight::get_intensity() const {
    return intensity_;
}

void AmbientLight::set_intensity(const Color& intensity) {
    intensity_ = intensity;
}

}  // namespace renderer
