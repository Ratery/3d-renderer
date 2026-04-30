#pragma once

#include <vector>

#include "Frame.h"
#include "RenderVertex.h"
#include "core/Triangle.h"
#include "scene/Scene.h"

namespace renderer {

class Renderer {
   public:
    Renderer(Scene& scene);

    Frame make_frame(Frame&& frame) const;

   private:
    Scene& scene_;
    std::vector<std::vector<float>> z_buffer_;

    void render_triangle(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP,
                         Frame& frame) const;

    void draw_triangle(const RenderVertex& v0, const RenderVertex& v1, const RenderVertex& v2,
                       Frame& frame) const;
};

}  // namespace renderer
