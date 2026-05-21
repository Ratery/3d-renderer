#include "rendering/Frame.h"

#include <algorithm>
#include <cassert>

namespace renderer {

Frame::Frame(Width width, Height height)
    : width_(width),
      height_(height),
      pixels_(4 * width_ * height_, 0.0f),
      z_buffer_(width_ * height_) {
    assert(width_ > 0 && height_ > 0);
    reset();
}

void Frame::reset() {
    std::ranges::fill(pixels_, 0.0f);
    std::uint32_t max_depth_uint = depth_to_uint(max_depth_);
    for (auto& z : z_buffer_) {
        z.store(max_depth_uint, std::memory_order_relaxed);
    }
}

bool Frame::is_depth_visible(Index x, Index y, float depth) const {
    uint32_t new_depth = depth_to_uint(depth);
    uint32_t current_depth = z_buffer(x, y).load(std::memory_order_relaxed);
    return new_depth < current_depth;
}

void Frame::set_pixel(Index x, Index y, float depth, const Color& color) {
    std::uint32_t new_depth = depth_to_uint(depth);
    auto& z = z_buffer(x, y);
    std::uint32_t current_depth = z.load(std::memory_order_relaxed);

    while (new_depth < current_depth) {
        if (z.compare_exchange_weak(current_depth, new_depth, std::memory_order_release,
                                    std::memory_order_relaxed)) {
            auto sf_color = make_sf_color(color);
            std::memcpy(&pixels(x, y), &sf_color, 4);
            return;
        }
    }
}

const std::vector<std::uint8_t>& Frame::get_pixels() const {
    return pixels_;
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

std::uint8_t& Frame::pixels(Index x, Index y) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return pixels_[4 * (x + y * width_)];
}

std::atomic<std::uint32_t>& Frame::z_buffer(Index x, Index y) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return z_buffer_[x + y * width_];
}

const std::atomic<std::uint32_t>& Frame::z_buffer(Index x, Index y) const {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return z_buffer_[x + y * width_];
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
