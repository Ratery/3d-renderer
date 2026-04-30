#include "Frame.h"

#include <cassert>

#include "SFML/Graphics/Color.hpp"

namespace renderer {

Frame::Frame(int width, int height) : width_(width), height_(height) {
    assert(width_ > 0 && height_ > 0);

    int size = width_ * height_;
    pixels_.resize(4 * size);
    z_buffer_.resize(size, -1.0f);
}

void Frame::reset_z_buffer() {
    z_buffer_.assign(width_ * height_, 1.0f);
}

void Frame::set_pixel(int x, int y, float depth, sf::Color color) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);

    if (z_buffer_[y * width_ + x] < depth) {
        return;
    }
    z_buffer_[y * width_ + x] = depth;

    int idx = 4 * (y * width_ + x);
    pixels_[idx] = color.r;
    pixels_[idx + 1] = color.g;
    pixels_[idx + 2] = color.b;
    pixels_[idx + 3] = color.a;

    // or memcpy(&pixels_[4 * (y * width_ + x)], &color, 4);
}

const std::vector<std::uint8_t>& Frame::get_pixels() const {
    return pixels_;
}

int Frame::get_width() const {
    return width_;
}

int Frame::get_height() const {
    return height_;
}

}  // namespace renderer
