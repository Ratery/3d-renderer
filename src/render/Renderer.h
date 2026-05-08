#pragma once

#include "Frame.h"
#include "core/Triangle.h"
#include "lighting/Material.h"
#include "lighting/PhongShader.h"
#include "scene/Scene.h"

namespace renderer {

class Renderer {
   public:
    Frame make_frame(const Scene& scene, Frame&& frame) const;

   private:
    constexpr static float eps = 1e-5f;

    Frame render_triangle(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP,
                          const Material& material, const PhongShader& shader, Frame&& frame) const;
};

}  // namespace renderer
