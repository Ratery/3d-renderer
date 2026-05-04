#include "Renderer.h"

#include "core/Color.h"
#include "core/Linalg.h"

namespace renderer {

namespace {

Vector2 ndc_to_screen(const Vector4& ndc, const Frame& frame) {
    return {(ndc.x() + 1.0f) / 2.0f * static_cast<float>(frame.width()),
            (1.0f - (ndc.y() + 1.0f) / 2.0f) * static_cast<float>(frame.height())};
}

Index clamp_start(float val, Index max_idx) {
    return std::clamp<Index>(static_cast<Index>(std::floor(val)), 0, max_idx);
}

Index clamp_end(float val, Index max_idx) {
    return std::clamp<Index>(static_cast<Index>(std::ceil(val)), 0, max_idx);
}

bool is_in_std_box(const Vector4& ndc) {
    return -1.0f <= ndc.x() && ndc.x() <= 1.0f && -1.0f <= ndc.y() && ndc.y() <= 1.0f &&
           -1.0f <= ndc.z() && ndc.z() <= 1.0f;
}

}  // namespace

Frame Renderer::render_triangle(Triangle triangle, const Matrix4& MVP, Frame&& frame) const {
    triangle.transform(MVP);
    Vector3 inv_z_row = triangle.get_vertices().row(3).cwiseInverse().eval();
    triangle.to_ndc();

    auto v0 = triangle.vertex(0);
    auto v1 = triangle.vertex(1);
    auto v2 = triangle.vertex(2);

    assert(is_in_std_box(v0));
    assert(is_in_std_box(v1));
    assert(is_in_std_box(v2));

    Vector2 p0 = ndc_to_screen(v0, frame);
    Vector2 p1 = ndc_to_screen(v1, frame);
    Vector2 p2 = ndc_to_screen(v2, frame);

    Index start_x = clamp_start(std::min({p0.x(), p1.x(), p2.x()}), frame.width() - 1);
    Index end_x = clamp_end(std::max({p0.x(), p1.x(), p2.x()}), frame.width() - 1);

    Index start_y = clamp_start(std::min({p0.y(), p1.y(), p2.y()}), frame.height() - 1);
    Index end_y = clamp_end(std::max({p0.y(), p1.y(), p2.y()}), frame.height() - 1);

    for (Index x = start_x; x <= end_x; x++) {
        for (Index y = start_y; y <= end_y; y++) {
            Vector2 u = Vector2(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f);

            float area = (p2 - p0).cross(p1 - p0);
            Vector3 w;
            w(1) = (p2 - p0).cross(u - p0) / area;
            w(2) = (u - p0).cross(p1 - p0) / area;
            w(0) = 1.0f - w(1) - w(2);

            if (w(0) >= -eps && w(1) >= -eps && w(2) >= -eps) {
                auto& ndc_z_row = triangle.get_vertices().row(2);
                float depth = ndc_z_row.dot(w);

                float inv_z = inv_z_row.dot(w);
                auto color_weights = inv_z_row.cwiseProduct(w) * (1.0f / inv_z);
                frame.set_pixel(x, y, depth, triangle.get_weighted_color(color_weights));
            }
        }
    }
    return frame;
}

Frame Renderer::make_frame(const Scene& scene, Frame&& frame) const {
    frame.reset_z_buffer();
    const auto& camera = scene.get_camera();
    auto VP = camera.make_projection_matrix() * camera.make_view_matrix();
    for (auto& object : scene.get_objects()) {
        for (auto& triangle : object.get_triangles()) {
            const auto& M = object.get_transform_matrix();
            auto MVP = VP * M;
            frame = render_triangle(triangle, MVP, std::move(frame));
        }
    }
    return frame;
}

}  // namespace renderer
