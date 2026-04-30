#pragma once

#include "core/Linalg.h"
#include "core/Vertex.h"

namespace renderer {

struct RenderVertex {
    RenderVertex(const Vertex& vertex, const Matrix4& MV, const Matrix4& MVP)
        : view_pos(MV * vertex.position), clip_pos(MVP * vertex.position) {}

    Vector3 ndc() const { return clip_pos.hnormalized(); }

    Vector4 view_pos;
    Vector4 clip_pos;
};

}  // namespace renderer
