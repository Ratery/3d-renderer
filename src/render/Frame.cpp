#include "Frame.h"

#include <cassert>

namespace renderer {

Frame::Frame(Width width, Height height)
    : width_(width),
      height_(height),
      pixels_(4 * width_ * height_),
      z_buffer_(width_ * height_, max_depth_) {
    assert(width_ > 0 && height_ > 0);
}

void Frame::reset_z_buffer() {
    z_buffer_.assign(width_ * height_, max_depth_);
}

void Frame::set_pixel(Index x, Index y, float depth, const Color& color) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);

    if (z_buffer(x, y) < depth) {
        return;
    }
    z_buffer(x, y) = depth;

    auto sf_color = make_sf_color(color);
    memcpy(&pixels(x, y), &sf_color, 4);
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

std::uint8_t& Frame::pixels(Index x, Index y) {
    return pixels_[4 * (x + y * width_)];
}

float& Frame::z_buffer(Index x, Index y) {
    return z_buffer_[x + y * width_];
}

sf::Color Frame::make_sf_color(const Color& color) {
    return {static_cast<std::uint8_t>(color.r() * 255.0f),
            static_cast<std::uint8_t>(color.g() * 255.0f),
            static_cast<std::uint8_t>(color.b() * 255.0f),
            static_cast<std::uint8_t>(color.a() * 255.0f)};
}

}  // namespace renderer
