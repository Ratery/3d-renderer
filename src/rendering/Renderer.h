#pragma once

#include "rendering/Frame.h"
#include "rendering/material/Material.h"
#include "rendering/pipeline/ClipPolygon.h"
#include "rendering/pipeline/ClipVertex.h"
#include "rendering/shading/PhongShader.h"
#include "scene/Scene.h"

namespace renderer {

enum FrustumPlaneType { Left, Right, Top, Bottom, Near, Far };

class Renderer {
   public:
    Frame make_frame(const Scene& scene, Frame&& frame) const;

   private:
    constexpr static float eps_ = 1e-5f;

    void rasterize_triangle(const ClipVertex& v0, const ClipVertex& v1, const ClipVertex& v2,
                            const Material& material, const PhongShader& shader,
                            Frame* frame) const;

    ClipPolygon clip_polygon_against_plane(const ClipPolygon& polygon_in,
                                           FrustumPlaneType plane) const;

    float eval_plane(FrustumPlaneType type, const Vector4& v) const;
};

}  // namespace renderer
