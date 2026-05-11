#include "ClipPolygon.h"

namespace renderer {

ClipPolygon::ClipPolygon() : count_(0) {}

ClipPolygon::ClipPolygon(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP)
    : count_(3) {
    auto view_normals = (MV * triangle.get_normals()).colwise().normalized();
    auto view_pos = MV * triangle.get_vertices();
    auto clip_pos = MVP * triangle.get_vertices();

    for (int i = 0; i < 3; i++) {
        vertices_[i].clip_pos = clip_pos.col(i);
        vertices_[i].view_pos = view_pos.col(i).head<3>();
        vertices_[i].view_normal = view_normals.col(i).head<3>();
    }
}

Index ClipPolygon::get_vertices_count() const {
    return count_;
}

const ClipVertex& ClipPolygon::get_vertex(Index index) const {
    return vertices_.at(index);
}

void ClipPolygon::push_vertex(const ClipVertex& vertex) {
    assert(count_ < 8);
    vertices_[count_] = vertex;
    count_++;
}

}  // namespace renderer
