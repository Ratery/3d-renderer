#include "Triangle.h"

namespace renderer {

Triangle::Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) : vertices_{v1, v2, v3} {}

std::array<Vertex, 3> Triangle::get_vertices() const {
    return vertices_;
}

}  // namespace renderer
