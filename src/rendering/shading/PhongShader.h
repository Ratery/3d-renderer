#pragma once

#include "core/Color.h"
#include "core/Linalg.h"
#include "rendering/lighting/AmbientLight.h"
#include "rendering/lighting/DirectionalLight.h"
#include "rendering/material/Material.h"

namespace renderer {

class PhongShader {
   public:
    PhongShader(const AmbientLight& ambient_light,
                const std::vector<DirectionalLight>& directional_lights,
                const Matrix4& view_matrix);

    Color shade(const Material& material, const Vector3& normal, const Vector3& view_pos,
                const Vector2& uv) const;

   private:
    AmbientLight ambient_light_;
    std::vector<DirectionalLight> directional_lights_;
};

}  // namespace renderer
