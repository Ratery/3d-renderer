#pragma once

#include <array>

#include "Vertex.h"

namespace renderer {

class Triangle {
   public:
    Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

    std::array<Vertex, 3> get_vertices() const;

   private:
    std::array<Vertex, 3> vertices_;
};

}  // namespace renderer
