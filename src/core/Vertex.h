#pragma once

#include "Color.h"
#include "Linalg.h"

namespace renderer {

struct Vertex {
    Vector4 position;
    Vector4 normal;
    Color color;
};

}  // namespace renderer
