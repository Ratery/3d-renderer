#include "Renderer.h"

#include "core/Linalg.h"
#include "lighting/Color.h"

namespace renderer {

namespace {

Vector2 ndc_to_screen(const Vector3& ndc, const Frame& frame) {
    return {(ndc.x() + 1.0f) / 2.0f * static_cast<float>(frame.width()),
            (1.0f - (ndc.y() + 1.0f) / 2.0f) * static_cast<float>(frame.height())};
}

Index clamp_start(float val, Index max_idx) {
    return std::clamp<Index>(static_cast<Index>(std::floor(val)), 0, max_idx);
}

Index clamp_end(float val, Index max_idx) {
    return std::clamp<Index>(static_cast<Index>(std::ceil(val)), 0, max_idx);
}

bool is_in_std_box(const Vector3& ndc, float eps) {
    return std::abs(ndc.x()) <= 1.0f + eps && std::abs(ndc.y()) <= 1.0f + eps &&
           std::abs(ndc.z()) <= 1.0f + eps;
}

ClipVertex interpolate_clip_vertex(const ClipVertex& a, const ClipVertex& b, float t) {
    return {a.clip_pos + t * (b.clip_pos - a.clip_pos), a.view_pos + t * (b.view_pos - a.view_pos),
            a.view_normal + t * (b.view_normal - a.view_normal)};
}

}  // namespace

Frame Renderer::rasterize_triangle(const ClipVertex& v0, const ClipVertex& v1, const ClipVertex& v2,
                                   const Material& material, const PhongShader& shader,
                                   Frame&& frame) const {
    Vector3 ndc_0 = v0.clip_pos.hnormalized();
    Vector3 ndc_1 = v1.clip_pos.hnormalized();
    Vector3 ndc_2 = v2.clip_pos.hnormalized();

    assert(is_in_std_box(ndc_0, eps_));
    assert(is_in_std_box(ndc_1, eps_));
    assert(is_in_std_box(ndc_2, eps_));

    Vector2 p0 = ndc_to_screen(ndc_0, frame);
    Vector2 p1 = ndc_to_screen(ndc_1, frame);
    Vector2 p2 = ndc_to_screen(ndc_2, frame);

    Index start_x = clamp_start(std::min({p0.x(), p1.x(), p2.x()}), frame.width() - 1);
    Index end_x = clamp_end(std::max({p0.x(), p1.x(), p2.x()}), frame.width() - 1);

    Index start_y = clamp_start(std::min({p0.y(), p1.y(), p2.y()}), frame.height() - 1);
    Index end_y = clamp_end(std::max({p0.y(), p1.y(), p2.y()}), frame.height() - 1);

    Matrix3 view_pos;
    view_pos << v0.view_pos, v1.view_pos, v2.view_pos;
    Matrix3 view_normals;
    view_normals << v0.view_normal, v1.view_normal, v2.view_normal;
    Vector3 inv_z_row = view_pos.row(2).cwiseInverse();

    for (Index x = start_x; x <= end_x; x++) {
        for (Index y = start_y; y <= end_y; y++) {
            Vector2 u = Vector2(static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f);

            float area = (p2 - p0).cross(p1 - p0);
            Vector3 w;
            w(1) = (p2 - p0).cross(u - p0) / area;
            w(2) = (u - p0).cross(p1 - p0) / area;
            w(0) = 1.0f - w(1) - w(2);

            if (w(0) >= -eps_ && w(1) >= -eps_ && w(2) >= -eps_) {
                float depth = Vector3(ndc_0.z(), ndc_1.z(), ndc_2.z()).dot(w);
                float inv_z = inv_z_row.dot(w);
                auto lerp_weights = inv_z_row.cwiseProduct(w) * (1.0f / inv_z);

                Vector3 frag_normal = (view_normals * lerp_weights).normalized();
                Vector3 frag_view_pos = view_pos * lerp_weights;
                Color color = shader.shade(material, frag_normal, frag_view_pos);
                frame.set_pixel(x, y, depth, color);
            }
        }
    }
    return frame;
}

Frame Renderer::make_frame(const Scene& scene, Frame&& frame) const {
    frame.reset();
    const auto& camera = scene.get_camera();
    const auto& view_matrix = camera.get_view_matrix();
    PhongShader shader(scene.get_ambient_light(), scene.get_directional_lights(), view_matrix);
    auto VP = camera.make_projection_matrix(frame.aspect_ratio()) * view_matrix;
    for (auto& object : scene.get_objects()) {
        const auto& material = object.get_material();
        for (auto& triangle : object.get_triangles()) {
            const auto& M = object.get_transform_matrix();
            auto MV = view_matrix * M;
            auto MVP = VP * M;

            auto polygon = ClipPolygon(triangle, MV, MVP);
            polygon = clip_polygon_against_plane(polygon, Near);
            polygon = clip_polygon_against_plane(polygon, Left);
            polygon = clip_polygon_against_plane(polygon, Right);
            polygon = clip_polygon_against_plane(polygon, Top);
            polygon = clip_polygon_against_plane(polygon, Bottom);
            polygon = clip_polygon_against_plane(polygon, Far);

            if (polygon.get_vertices_count() >= 3) {
                const auto& v0 = polygon.get_vertex(0);
                for (Index i = 1; i + 1 < polygon.get_vertices_count(); i++) {
                    const auto& v1 = polygon.get_vertex(i);
                    const auto& v2 = polygon.get_vertex(i + 1);
                    frame = rasterize_triangle(v0, v1, v2, material, shader, std::move(frame));
                }
            }
        }
    }
    return frame;
}

ClipPolygon Renderer::clip_polygon_against_plane(const ClipPolygon& polygon_in,
                                                 FrustumPlaneType plane) const {
    ClipPolygon polygon_out;
    const Index n = polygon_in.get_vertices_count();
    for (Index i = 0; i < n; i++) {
        const auto& current = polygon_in.get_vertex(i);
        const auto& next = polygon_in.get_vertex((i + 1) % n);

        float current_val = eval_plane(plane, current.clip_pos);
        float next_val = eval_plane(plane, next.clip_pos);

        bool is_current_inside = current_val >= 0.0f;
        bool is_next_inside = next_val >= 0.0f;

        if (is_current_inside && is_next_inside) {
            polygon_out.push_vertex(next);
        } else if (is_current_inside) {
            float t = current_val / (current_val - next_val);
            polygon_out.push_vertex(interpolate_clip_vertex(current, next, t));
        } else if (is_next_inside) {
            float t = current_val / (current_val - next_val);
            polygon_out.push_vertex(interpolate_clip_vertex(current, next, t));
            polygon_out.push_vertex(next);
        }
    }
    return polygon_out;
}

float Renderer::eval_plane(FrustumPlaneType type, const Vector4& v) const {
    switch (type) {
        case Left:
            return v.x() + v.w();
        case Right:
            return -v.x() + v.w();
        case Bottom:
            return v.y() + v.w();
        case Top:
            return -v.y() + v.w();
        case Near:
            return v.z() + v.w();
        case Far:
            return -v.z() + v.w();
    }
    return 0.0f;
}

}  // namespace renderer
