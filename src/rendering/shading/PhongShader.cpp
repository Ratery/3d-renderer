#include "rendering/shading/PhongShader.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace renderer {

namespace {

bool is_normalized(const Vector3& vec) {
    return std::abs(vec.norm() - 1.0f) < 1e-5f;
}

}  // namespace

PhongShader::PhongShader(const AmbientLight& ambient_light,
                         const std::vector<DirectionalLight>& directional_lights,
                         const Matrix4& view_matrix)
    : ambient_light_(ambient_light) {
    directional_lights_.reserve(directional_lights.size());
    for (const auto& light : directional_lights) {
        directional_lights_.emplace_back(light.make_transformed(view_matrix));
    }
}

Color PhongShader::shade(const Material& material, const Vector3& normal,
                         const Vector3& view_pos, const Vector2& uv) const {
    assert(is_normalized(normal));

    Vector3 view_to_surface = -view_pos.normalized();
    Color diffuse_color = material.get_albedo();
    if (material.get_diffuse_map()) {
        diffuse_color *= material.get_diffuse_map()->sample(uv);
    }

    Color final_color = diffuse_color * ambient_light_.get_intensity();
    for (const auto& light : directional_lights_) {
        const auto& light_to_surface = -light.get_direction();
        assert(is_normalized(light_to_surface));

        float cos_theta = normal.dot(light_to_surface);
        if (cos_theta >= 0.0f) {  // if surface face towards light source
            Color diffuse_term = diffuse_color * light.get_intensity() * cos_theta;

            Vector3 halfway_vec = (light_to_surface + view_to_surface).normalized();
            float specular_factor =
                std::pow(std::max(0.0f, normal.dot(halfway_vec)), material.get_shininess());
            Color specular_term = material.get_specular() * light.get_intensity() * specular_factor;

            final_color += diffuse_term + specular_term;
        }
    }
    return final_color;
}

}  // namespace renderer
