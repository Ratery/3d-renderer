#include "rendering/pipeline/ClipPolygon.h"

#include <cassert>

namespace renderer {

ClipPolygon::ClipPolygon() : vertices_({}), count_(0) {}

ClipPolygon::ClipPolygon(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP)
    : vertices_({}), count_(3) {
    Matrix4x3 view_pos;
    view_pos.noalias() = MV * triangle.get_vertices();
    Matrix4x3 view_normals;
    view_normals.noalias() = (MV * triangle.get_normals()).colwise().normalized();
    Matrix4x3 clip_pos;
    clip_pos.noalias() = MVP * triangle.get_vertices();

    for (int i = 0; i < 3; i++) {
        vertices_[i].clip_pos = clip_pos.col(i);
        vertices_[i].view_pos = view_pos.col(i).head<3>();
        vertices_[i].view_normal = view_normals.col(i).head<3>();
        vertices_[i].uv = triangle.uv(i);
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
