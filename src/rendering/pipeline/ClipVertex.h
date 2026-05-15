#pragma once

#include "core/Linalg.h"

namespace renderer {

struct ClipVertex {
    Vector4 clip_pos;
    Vector3 view_pos;
    Vector3 view_normal;
    Vector2 uv;
};

}  // namespace renderer
