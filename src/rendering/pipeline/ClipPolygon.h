#pragma once

#include <array>

#include "core/Linalg.h"
#include "core/Triangle.h"
#include "rendering/pipeline/ClipVertex.h"

namespace renderer {

class ClipPolygon {
   public:
    ClipPolygon();
    ClipPolygon(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP);

    Index get_vertices_count() const;

    const ClipVertex& get_vertex(Index index) const;
    void push_vertex(const ClipVertex& vertex);

   private:
    std::array<ClipVertex, 8> vertices_;
    Index count_;
};

}  // namespace renderer
