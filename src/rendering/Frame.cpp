#include "rendering/Frame.h"

#include <algorithm>
#include <cassert>

namespace renderer {

Frame::Frame(Width width, Height height)
    : width_(width),
      height_(height),
      sample_colors_(msaa_samples_ * width_ * height_),
      resolved_pixels_(4 * width_ * height_, 0.0f),
      z_buffer_(msaa_samples_ * width_ * height_) {
    assert(width_ > 0 && height_ > 0);
    reset();
}

void Frame::reset() {
    std::ranges::fill(sample_colors_, Color(0.0f, 0.0f, 0.0f));
    std::uint32_t max_depth_uint = depth_to_uint(max_depth_);
    for (auto& z : z_buffer_) {
        z.store(max_depth_uint, std::memory_order_relaxed);
    }
}

bool Frame::is_depth_visible(Index x, Index y, Index sample_id, float depth) const {
    uint32_t new_depth = depth_to_uint(depth);
    uint32_t current_depth = z_buffer(x, y, sample_id).load(std::memory_order_relaxed);
    return new_depth < current_depth;
}

void Frame::set_color(Index x, Index y, Index sample_id, float depth, const Color& color) {
    std::uint32_t new_depth = depth_to_uint(depth);
    auto& z = z_buffer(x, y, sample_id);
    std::uint32_t current_depth = z.load(std::memory_order_relaxed);

    while (new_depth < current_depth) {
        if (z.compare_exchange_weak(current_depth, new_depth, std::memory_order_release,
                                    std::memory_order_relaxed)) {
            sample_colors(x, y, sample_id) = color;
            return;
        }
    }
}

void Frame::resolve() {
    for (Index y = 0; y < height_; y++) {
        for (Index x = 0; x < width_; x++) {
            Color res_color;

            for (Index sample_id = 0; sample_id < msaa_samples_; sample_id++) {
                res_color += sample_colors(x, y, sample_id);
            }
            res_color /= msaa_samples_;

            auto sf_color = make_sf_color(res_color.clamped());
            std::memcpy(&resolved_pixels_[4 * (x + y * width_)], &sf_color, 4);
        }
    }
}

const std::vector<std::uint8_t>& Frame::get_resolved_pixels() const {
    return resolved_pixels_;
}

Width Frame::width() const {
    return Width{width_};
}

Height Frame::height() const {
    return Height{height_};
}

float Frame::aspect_ratio() const {
    return static_cast<float>(height_) / static_cast<float>(width_);
}

Color& Frame::sample_colors(Index x, Index y, Index sample_id) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return sample_colors_[msaa_samples_ * (x + y * width_) + sample_id];
}

std::atomic<std::uint32_t>& Frame::z_buffer(Index x, Index y, Index sample_id) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return z_buffer_[msaa_samples_ * (x + y * width_) + sample_id];
}

const std::atomic<std::uint32_t>& Frame::z_buffer(Index x, Index y, Index sample_id) const {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return z_buffer_[msaa_samples_ * (x + y * width_) + sample_id];
}

std::uint32_t Frame::depth_to_uint(float depth) {
    std::uint32_t result;
    std::memcpy(&result, &depth, sizeof(float));
    return result;
}

float Frame::uint_to_depth(std::uint32_t value) {
    float result;
    std::memcpy(&result, &value, sizeof(float));
    return result;
}

sf::Color Frame::make_sf_color(const Color& color) {
    return {static_cast<std::uint8_t>(color.r() * 255.0f),
            static_cast<std::uint8_t>(color.g() * 255.0f),
            static_cast<std::uint8_t>(color.b() * 255.0f),
            static_cast<std::uint8_t>(color.a() * 255.0f)};
}

}  // namespace renderer
