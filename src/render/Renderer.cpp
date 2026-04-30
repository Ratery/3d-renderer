#include "Renderer.h"

#include "SFML/Graphics/Color.hpp"

namespace renderer {

Renderer::Renderer(Scene& scene) : scene_(scene) {}

void Renderer::render_triangle(const Triangle& triangle, const Matrix4& MV, const Matrix4& MVP,
                               Frame& frame) const {
    auto rv0 = RenderVertex(triangle.get_vertices()[0], MV, MVP);
    auto rv1 = RenderVertex(triangle.get_vertices()[1], MV, MVP);
    auto rv2 = RenderVertex(triangle.get_vertices()[2], MV, MVP);

    // clipping

    draw_triangle(rv0, rv1, rv2, frame);
}

void Renderer::draw_triangle(const RenderVertex& v0, const RenderVertex& v1, const RenderVertex& v2,
                             Frame& frame) const {
    auto ndc_to_screen = [&frame](const Vector3& ndc) {
        return Vector2((ndc.x() + 1.0f) / 2.0f * frame.get_width(),
                       (1.0f - (ndc.y() + 1.0f) / 2.0f) * frame.get_height());
    };

    // check NDC
    for (int i = 0; i < 3; i++) {
        assert(-1.0f <= v0.ndc()[i] && v0.ndc()[i] <= 1.0f);
        assert(-1.0f <= v1.ndc()[i] && v1.ndc()[i] <= 1.0f);
        assert(-1.0f <= v2.ndc()[i] && v2.ndc()[i] <= 1.0f);
    }

    Vector2 p0 = ndc_to_screen(v0.ndc());
    Vector2 p1 = ndc_to_screen(v1.ndc());
    Vector2 p2 = ndc_to_screen(v2.ndc());

    int min_x = static_cast<int>(std::floor(std::min({p0.x(), p1.x(), p2.x()})));
    min_x = std::max(0, min_x);

    int max_x = static_cast<int>(std::ceil(std::max({p0.x(), p1.x(), p2.x()})));
    max_x = std::min(max_x, frame.get_width() - 1);

    int min_y = static_cast<int>(std::floor(std::min({p0.y(), p1.y(), p2.y()})));
    min_y = std::max(0, min_y);

    int max_y = static_cast<int>(std::ceil(std::max({p0.y(), p1.y(), p2.y()})));
    max_y = std::min(max_y, frame.get_height() - 1);

    for (int x = std::max(0, min_x); x <= std::min(max_x, frame.get_width() - 1); x++) {
        for (int y = min_y; y <= max_y; y++) {
            Vector2 u = Vector2(x + 0.5f, y + 0.5f);

            float w = (p2 - p0).cross(p1 - p0);
            float w1 = (p2 - p0).cross(u - p0) / w;
            float w2 = (u - p0).cross(p1 - p0) / w;
            float w0 = 1.0f - w1 - w2;

            if (w0 >= -EPS && w1 >= -EPS && w2 >= -EPS) {
                float depth = w0 * v0.ndc().z() + w1 * v1.ndc().z() + w2 * v2.ndc().z();
                frame.set_pixel(x, y, depth, sf::Color::Red);
            }
        }
    }
}

Frame Renderer::make_frame(Frame&& frame) const {
    frame.reset_z_buffer();
    const auto& camera = scene_.get_camera();
    auto VP = camera.get_projection_matrix() * camera.get_view_matrix().inverse();
    for (auto& object : scene_.get_objects()) {
        for (auto& triangle : object.get_triangles()) {
            auto& M = object.get_transform_matrix();
            auto MV = camera.get_view_matrix().inverse() * M;
            auto MVP = VP * M;
            render_triangle(triangle, MV, MVP, frame);
        }
    }
    return frame;
}

}  // namespace renderer
