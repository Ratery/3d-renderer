#pragma once

#include "AmbientLight.h"
#include "Color.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "core/Linalg.h"

namespace renderer {

class PhongShader {
   public:
    PhongShader(const AmbientLight& ambient_light,
                const std::vector<DirectionalLight>& directional_lights,
                const Matrix4& view_matrix);

    Color shade(const Material& material, const Vector3& normal, const Vector3& view_pos) const;

   private:
    AmbientLight ambient_light_;
    std::vector<DirectionalLight> directional_lights_;
};

}  // namespace renderer
