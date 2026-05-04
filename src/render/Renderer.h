#pragma once

#include "Frame.h"
#include "core/Triangle.h"
#include "scene/Scene.h"

namespace renderer {

class Renderer {
   public:
    Frame make_frame(const Scene& scene, Frame&& frame) const;

   private:
    constexpr static float eps = 1e-5f;

    Frame render_triangle(Triangle triangle, const Matrix4& MVP, Frame&& frame) const;
};

}  // namespace renderer
