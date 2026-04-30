#pragma once

#include "core/Color.h"
#include "core/Linalg.h"
#include "core/Vertex.h"

namespace renderer {

struct RenderVertex {
    RenderVertex(const Vertex& vertex, const Matrix4& MV, const Matrix4& MVP)
        : view_pos(MV * vertex.position), clip_pos(MVP * vertex.position), color(vertex.color) {}

    Vector3 ndc() const { return clip_pos.hnormalized(); }

    float inv_z() const { return 1.0f / view_pos.z(); }

    Vector4 view_pos;
    Vector4 clip_pos;
    Color color;
};

}  // namespace renderer
