#include "Material.h"

namespace renderer {

Material::Material(const Color& albedo, const Color& specular, float shininess)
    : albedo_(albedo), specular_(specular), shininess_(shininess) {}

const Color& Material::get_albedo() const {
    return albedo_;
}

const Color& Material::get_specular() const {
    return specular_;
}

float Material::get_shininess() const {
    return shininess_;
}

void Material::set_albedo(const Color& albedo) {
    albedo_ = albedo;
}

void Material::set_specular(const Color& specular) {
    specular_ = specular;
}

void Material::set_shininess(float shininess) {
    shininess_ = shininess;
}

}  // namespace renderer
